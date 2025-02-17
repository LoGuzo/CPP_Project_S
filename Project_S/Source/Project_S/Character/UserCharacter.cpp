// Fill out your copyright notice in the Description page of Project Settings.


#include "UserCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Project_S/MappingClass.h"
#include "Net/UnrealNetwork.h"
#include "Project_S/AnimInstance/UserAnimInstance.h"
#include "Project_S/Component/C_EqiupComponent.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include "Project_S/Component/C_QuickSlotComponent.h"
#include "Project_S/Item/WeaponActor.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Widget/S_CharacterWidget.h"
#include "Project_S/Widget/W_CharInfo.h"
#include "Project_S/Widget/W_ChatBalloon.h"
#include "Project_S/Widget/W_QuestSystem.h"

AUserCharacter::AUserCharacter()
{
	MyCharType = E_CharacterType::E_User;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	bIsFlipFlopInventoryActive = false;
	bIsFlipFlopEquipmentActive = false;
	bIsFlipFlopSkillWidgetActive = false;
	IsAttacking = false;

	MyWeapon = nullptr;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetRelativeLocation(FVector(-110.f, 0.f, 212.f));
	FollowCamera->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/Mannequin/Animations/Infinity/BP_WarriorAnim.BP_WarriorAnim_C'"));
	if (ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ANIM.Class);

	Inventory = CreateDefaultSubobject<UC_InventoryComponent>(TEXT("INVENTORY"));
	Equip = CreateDefaultSubobject<UC_EqiupComponent>(TEXT("EQUIP"));
	QuickSlot = CreateDefaultSubobject<UC_QuickSlotComponent>(TEXT("QUICK"));

	static ConstructorHelpers::FClassFinder<US_CharacterWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_UserWidget.WBP_UserWidget_C'"));
	if (UW.Succeeded())
		CharacterUI = UW.Class;

	static ConstructorHelpers::FClassFinder<UCameraShakeBase>CS(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/BP_UserCameraShake.BP_UserCameraShake_C'"));
	if (CS.Succeeded())
		TCameraShake = CS.Class;
	
	SpeechBubble = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubble"));
	SpeechBubble->SetWidgetSpace(EWidgetSpace::Screen);
	SpeechBubble->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget>SB(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_ChatBalloon.WBP_ChatBalloon_C'"));
	if (SB.Succeeded())
	{
		SpeechBubble->SetWidgetClass(SB.Class);
		SpeechBubble->SetDrawSize(FVector2D(500.f, 200.f));
		SpeechBubble->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	}
}

void AUserCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUserCharacter::Dash);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUserCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUserCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AUserCharacter::Attack);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AUserCharacter::OnInventoryKeyPressed);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AUserCharacter::OnEquipmentKeyPressed);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AUserCharacter::PickUpItem);
	PlayerInputComponent->BindAction("SkillWidget", IE_Pressed, this, &AUserCharacter::OnSkillWidgetKeyPressed);

	PlayerInputComponent->BindAction("Quick1", IE_Pressed, this, &AUserCharacter::UseQuickSlot);
	PlayerInputComponent->BindAction("Quick2", IE_Pressed, this, &AUserCharacter::UseQuickSlot);
	PlayerInputComponent->BindAction("Quick3", IE_Pressed, this, &AUserCharacter::UseQuickSlot);
	PlayerInputComponent->BindAction("Quick4", IE_Pressed, this, &AUserCharacter::UseQuickSlot);
	PlayerInputComponent->BindAction("Quick5", IE_Pressed, this, &AUserCharacter::UseQuickSlot);
	PlayerInputComponent->BindAction("Quick6", IE_Pressed, this, &AUserCharacter::UseQuickSlot);
	PlayerInputComponent->BindAction("Quick7", IE_Pressed, this, &AUserCharacter::UseQuickSlot);

}
void AUserCharacter::SetMesh(E_CharClass _ClassType)
{
	ClassType = _ClassType;
	MappingClass* CharacterTypeMapping = new MappingClass();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		ClassData = StaticCastSharedPtr<FCharacterClass>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_CharClassData)->GetMyData(CharacterTypeMapping->GetCharacterDescription(_ClassType)));
		if (ClassData.IsValid())
		{
			MeshPath = Cast<USkeletalMesh>(ClassData.Pin()->ClassMesh.LoadSynchronous());
			//GetMesh()->SetAnimInstanceClass(ClassData.Pin()->ClassAnim.LoadSynchronous());
			OnRep_MeshPath();	
		}
	}
}

void AUserCharacter::OnRep_MeshPath()
{
	if (MeshPath && GetMesh())
	{
		GetMesh()->SetSkeletalMesh(MeshPath);
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	}

	AnimInstance = Cast<UUserAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->SetPlayer(this);
		AnimInstance->OnAttackHit.AddUObject(this, &AUserCharacter::AttackCheck);
		AnimInstance->OnMontageEnded.AddDynamic(this, &AUserCharacter::OnAttackMontageEnd);
	}

	if (HUDWidget)
		HUDWidget->GetCharInfo()->SetImg(ClassType);
}

void AUserCharacter::ShotAttackCheck()
{
	if (MyWeapon)
		MyWeapon->Fire();
}

void AUserCharacter::UpdateQuest(const TArray<FQuestNode*>& Slots)
{
	if (HUDWidget)
		HUDWidget->GetQuestSystem()->UpdateSlots(Slots);
}

void AUserCharacter::SetChatBalloon(const FText& Message)
{
	if (ChatBalloon)
	{
		ChatBalloon->SetRenderOpacity(1.f);
		ChatBalloon->SetSpeechBubble(Message);
	}

	GetWorldTimerManager().ClearTimer(CloseChatBalloon);
	GetWorldTimerManager().SetTimer(CloseChatBalloon, this, &AUserCharacter::HideChatBalloon, 5.f, false);
}

void AUserCharacter::BeginPlay()
{
	Super::BeginPlay();

	SaveLocation = GetActorLocation();
}

void AUserCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveCharacterData();

	if (LoadData.IsValid())
		LoadData.Reset();

	if (NowSkill.IsValid())
		NowSkill.Reset();

	if (ClassData.IsValid())
		ClassData.Reset();

	RemoveMyWeapon();

	GetWorldTimerManager().ClearTimer(UnusedHandle);
	GetWorldTimerManager().ClearTimer(HitHandle);
	GetWorldTimerManager().ClearTimer(CloseChatBalloon);
}

float AUserCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Stat->GetHp() <= 0)
		UserDied();

	if (TCameraShake)
		PlayCameraShake(TCameraShake);

	if (HUDWidget && HUDWidget->GetCharInfo())
		HUDWidget->GetCharInfo()->ShakeHealthBar();

	if (DamageCauser)
	{
		float HitDirectionAngle = CalculateHitDirectionAngle(DamageCauser->GetActorLocation());
		if (AnimInstance)
		{
			AnimInstance->SetDirection(HitDirectionAngle);
			AnimInstance->SetIsHit(true);
			GetWorldTimerManager().SetTimer(HitHandle, this, &AUserCharacter::SetHitFalse, 0.1f, false);
		}
	}
	return DamageAmount;
}

void AUserCharacter::ResetStat()
{
	Stat->SetHp(Stat->GetMaxHp());
}

void AUserCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (CharacterUI)
		HUDWidget = CreateWidget<US_CharacterWidget>(GetWorld(), CharacterUI);

	SpeechBubble->InitWidget();
	ChatBalloon = Cast<UW_ChatBalloon>(SpeechBubble->GetUserWidgetObject());
	if (ChatBalloon)
		HideChatBalloon();
}

void AUserCharacter::SetUserWidget()
{
	if (HUDWidget)
	{
		HUDWidget->GetCharInfo()->BindLvl(Stat);
		HUDWidget->GetCharInfo()->BindHp(Stat);
		HUDWidget->GetCharInfo()->BindMp(Stat);
		HUDWidget->GetCharInfo()->BindExp(Stat);
		HUDWidget->ShowQuick(QuickSlot);
		SetWidget();
	}
}

void AUserCharacter::SetMyParty(UPartySystem* _MyParty)
{
	MyParty = _MyParty;
}

void AUserCharacter::SaveCharacterData()
{
	FMyCharacterData NowCharData;
	NowCharData.CharID = GetCharID();
	NowCharData.Type = ClassType;
	NowCharData.Level = Stat->GetLevel();
	NowCharData.Exp = Stat->GetExp();
	NowCharData.MyEquip = Equip->GetSlots();
	NowCharData.MyInventory = Inventory->GetSlots();
	NowCharData.MySkillQuick = QuickSlot->GetSkillSlots();
	NowCharData.MyPotionQuick = QuickSlot->GetPotionSlots();

	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (GetCharID() != "")
			MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->SetMyData(GetCharID(), &NowCharData);
	}
}

void AUserCharacter::LoadCharacterData()
{
	FTimerHandle LoadDelay;
	GetWorldTimerManager().SetTimer(LoadDelay, this, &AUserCharacter::DelayedLoadCharacterData, 1.f, false);
}

void AUserCharacter::DelayedLoadCharacterData()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (GetCharID() != "") {
			LoadData = StaticCastSharedPtr<FMyCharacterData>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->GetMyData(GetCharID()));
			if (LoadData.IsValid())
			{
				SetClass(LoadData.Pin()->Type);
				SetMesh(LoadData.Pin()->Type);
				Stat->SetLevel(LoadData.Pin()->Level);
				Stat->SetExp(LoadData.Pin()->Exp);
				Equip->SetSlots(LoadData.Pin()->MyEquip);
				Inventory->SetSlots(LoadData.Pin()->MyInventory);
				QuickSlot->SetSkillSlots(LoadData.Pin()->MySkillQuick);
				QuickSlot->SetPotionSlots(LoadData.Pin()->MyPotionQuick);
			}

			for (const FS_Slot& slot : Equip->GetSlots())
			{
				if (slot.ItemClass != nullptr)
					SetMyWeapon(slot.ItemClass);
			}

			QuickSlot->OnQuickUpdated.Broadcast();
		}
	}
}

void AUserCharacter::SetClass(E_CharClass _ClassType)
{
	ClassType = _ClassType;
}

void AUserCharacter::MoveForward(float Value)
{
	if (!IsAttacking) {
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AUserCharacter::MoveRight(float Value)
{
	if (!IsAttacking) {
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void AUserCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeLine.TickTimeline(DeltaTime);
}

void AUserCharacter::Server_PickUpItem_Implementation()
{
	Multi_PickUpItem();
}

bool AUserCharacter::Server_PickUpItem_Validate()
{
	return true;
}
void AUserCharacter::Multi_PickUpItem_Implementation()
{
	if (GetCurItem() != nullptr) {
		GetCurItem()->GetC_ItemComponent()->Interact(this);
		
		Inventory->OnInventoryUpdated.Broadcast();
		QuickSlot->OnQuickUpdated.Broadcast();
	}
}
void AUserCharacter::PickUpItem()
{
	if (HasAuthority())
		Multi_PickUpItem();
	else
		Server_PickUpItem();
}

void AUserCharacter::TimelineProgress(float _Value)
{
	GetMesh()->SetRelativeRotation(FRotator(BeforeRot.Pitch, FMath::Lerp(BeforeRot.Yaw, BeforeRot.Yaw + float(360 * 12), _Value), BeforeRot.Roll));
}

void AUserCharacter::SetMyWeapon(TSubclassOf<class AA_Item> _MyWeapon)
{
	if (HasAuthority())
		Multi_SetMyWeapon(_MyWeapon);
	else
		Server_SetMyWeapon(_MyWeapon);
}

void AUserCharacter::Server_SetMyWeapon_Implementation(TSubclassOf<class AA_Item> _MyWeapon)
{
	Multi_SetMyWeapon(_MyWeapon);
}

bool AUserCharacter::Server_SetMyWeapon_Validate(TSubclassOf<class AA_Item> _MyWeapon)
{
	return true;
}

void AUserCharacter::Multi_SetMyWeapon_Implementation(TSubclassOf<class AA_Item> _MyWeapon)
{
	if (MyWeapon)
		return;

	if (HasAuthority())
	{
		MyWeapon = GetWorld()->SpawnActor<AWeaponActor>(*_MyWeapon);
		MyWeapon->SetItem(Equip->GetSlot(0).ItemName.ToString());
		MyWeapon->SetWeaponOwner(this);
		OnRep_MyWeapon();
	}
}

void AUserCharacter::OnRep_MyWeapon()
{
	if (MyWeapon)
	{
		FName WeaponSocket(TEXT("r_hand_sword"));
		MyWeapon->GetBoxCollision()->SetSimulatePhysics(false);
		MyWeapon->GetBoxCollision()->SetCollisionProfileName(TEXT("NoCollision"));
		MyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		MyWeapon->SetOwner(this);

		if (AnimInstance)
			AnimInstance->SetHaveWeapon(true);
	}
}

void AUserCharacter::RemoveMyWeapon()
{
	if (HasAuthority())
		Multi_RemoveMyWeapon();
	else
		Server_RemoveMyWeapon();
}

void AUserCharacter::Server_RemoveMyWeapon_Implementation()
{
	Multi_RemoveMyWeapon();
}

bool AUserCharacter::Server_RemoveMyWeapon_Validate()
{
	return true;
}

void AUserCharacter::Multi_RemoveMyWeapon_Implementation()
{
	if (MyWeapon)
	{
		MyWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		MyWeapon->SetOwner(nullptr);
		MyWeapon->Destroy();
		MyWeapon = nullptr;
	}

	if (AnimInstance)
		AnimInstance->SetHaveWeapon(false);
}

void AUserCharacter::Attack()
{
	if (nullptr != MyWeapon)
	{
		if (IsAttacking)
			return;

		AttackMontage();
		IsAttacking = true;
	}
}

void AUserCharacter::AttackMontage()
{
	if (HasAuthority())
		Multi_AttackMontage();
	else
		Server_AttackMontage();
}

void AUserCharacter::Server_AttackMontage_Implementation()
{
	Multi_AttackMontage();
}

bool AUserCharacter::Server_AttackMontage_Validate()
{
	return true;
}

void AUserCharacter::Multi_AttackMontage_Implementation()
{
	if (!AnimInstance)
		return;

	switch (ClassType)
	{
	case E_CharClass::E_Warrior:
		AnimInstance->OnHandSwordPlayAM();
		AnimInstance->JumpToSection(AttackIndex, 0);
		break;
	case E_CharClass::E_Magician:
		AnimInstance->OnHandStaffPlayAM();
		AnimInstance->JumpToSection(AttackIndex, 1);
		break;
	}

	AttackIndex = (AttackIndex + 1) % 3;
}

void AUserCharacter::OnAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

void AUserCharacter::UseQuickSlot()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (PlayerController->IsInputKeyDown(EKeys::One))
		{
			if (QuickSlot->GetSkillSlot(0) != "None")
				UseSkill(QuickSlot->GetSkillSlot(0));
		}
		if (PlayerController->IsInputKeyDown(EKeys::Two))
		{
			if (QuickSlot->GetSkillSlot(1) != "None")
				UseSkill(QuickSlot->GetSkillSlot(1));
		}
		if (PlayerController->IsInputKeyDown(EKeys::Three))
		{
			if (QuickSlot->GetSkillSlot(2) != "None")
				UseSkill(QuickSlot->GetSkillSlot(2));
		}
		if (PlayerController->IsInputKeyDown(EKeys::Four))
		{
			if (QuickSlot->GetSkillSlot(3) != "None")
				UseSkill(QuickSlot->GetSkillSlot(3));
		}
		if (PlayerController->IsInputKeyDown(EKeys::Five))
		{
			if (QuickSlot->GetSkillSlot(4) != "None")
				UseSkill(QuickSlot->GetSkillSlot(4));
		}
		if (PlayerController->IsInputKeyDown(EKeys::Six))
		{
			if (Stat->GetHp() <= Stat->GetMaxHp())
			{
				if (QuickSlot->GetPotionSlot(0) != "None")
					UseItem(0);
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Seven))
		{
			if (Stat->GetMp() <= Stat->GetMaxMp())
			{
				if (QuickSlot->GetPotionSlot(1) != "None")
					UseItem(1);
			}
		}
	}
}

void AUserCharacter::AttackCheck()
{
	if (nullptr != MyWeapon)
		MeleeAttackCheck(150.f);
}

void AUserCharacter::OnInventoryKeyPressed()
{

	if (!bIsFlipFlopInventoryActive)
	{
		HUDWidget->ShowInventory();
		bIsFlipFlopInventoryActive = true;
	}
	else
	{
		HUDWidget->RemoveInventory();
		bIsFlipFlopInventoryActive = false;
	}
}

void AUserCharacter::OnEquipmentKeyPressed()
{
	if (!bIsFlipFlopEquipmentActive)
	{
		HUDWidget->ShowEquip();
		bIsFlipFlopEquipmentActive = true;
	}
	else
	{
		HUDWidget->RemoveEquip();
		bIsFlipFlopEquipmentActive = false;
	}
}

void AUserCharacter::OnSkillWidgetKeyPressed()
{
	if (!bIsFlipFlopSkillWidgetActive)
	{
		HUDWidget->ShowSkillW();
		bIsFlipFlopSkillWidgetActive = true;
	}
	else
	{
		HUDWidget->RemoveSillW();
		bIsFlipFlopSkillWidgetActive = false;
	}
}

void AUserCharacter::SetCurItem(AA_Item* _Curitem)
{
	Curitem = _Curitem;
}

void AUserCharacter::AnyMove(UCurveBase* _SkillCurve)
{
	BeforeRot = GetMesh()->GetRelativeRotation();
	auto SkillCurve = Cast<UCurveFloat>(_SkillCurve);
	if (SkillCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));

		CurveTimeLine.AddInterpFloat(SkillCurve, TimelineProgress);
		CurveTimeLine.SetLooping(false);
		CurveTimeLine.PlayFromStart();
	}
}

void AUserCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass)
{
	if (ShakeClass)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController && PlayerController->PlayerCameraManager)
			PlayerController->PlayerCameraManager->StartCameraShake(ShakeClass);
	}
}

void AUserCharacter::Dash()
{
	if (HasAuthority())
		Multi_Dash();
	else
		Server_Dash();
}
void AUserCharacter::Server_Dash_Implementation()
{
	Multi_Dash();
}

bool AUserCharacter::Server_Dash_Validate()
{
	return true;
}

void AUserCharacter::Multi_Dash_Implementation()
{
	FVector LastInputVector = GetCharacterMovement()->GetLastInputVector();
	if (LastInputVector.IsNearlyZero())
		LastInputVector = GetActorForwardVector();
	else
		LastInputVector = LastInputVector.GetSafeNormal();
	LastInputVector.Z = 0;

	GetCharacterMovement()->BrakingFrictionFactor = 0.f;
	LaunchCharacter(LastInputVector * 5000.f, true, true);

	if (AnimInstance)
		AnimInstance->SetOnDash(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Dash"));

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AUserCharacter::StopDashing, 0.1f, false);
}

void AUserCharacter::StopDashing() {
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AUserCharacter::ResetDash, 0.1f, false);
}

void AUserCharacter::ResetDash()
{
	if (AnimInstance)
		AnimInstance->SetOnDash(false);
}

void AUserCharacter::Multi_UseSkill(const FString& SkillName)
{
	Super::Multi_UseSkill(SkillName);
}

void AUserCharacter::Multi_UseSkill_Implementation(const FString& _SkillName)
{
	const auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		const auto SkillData = StaticCastSharedPtr<FSkillTable>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Skill)->GetMyData((Skill->GetSlot(0).ItemName).ToString()));
		NowSkill = SkillData;
		if (SkillData.IsValid())
			AnimInstance->PlaySome(SkillData);
	}
}

void AUserCharacter::UseItem(const int32 QuickIndex)
{
	UsePotion(QuickSlot->GetPotionSlots()[QuickIndex].Amount, QuickSlot->GetPotionSlots()[QuickIndex].ItemName.ToString());
	QuickSlot->UsePotionSlot(QuickIndex);
}

void AUserCharacter::UsePotion(const int32 StackSize, const FString& ItemName)
{
	int32 LeastIndex = -1;
	int32 SumSize = 0;
	int32 index = 0;
	for (const FS_Slot& slot : Inventory->GetSlots())
	{
		if (slot.ItemName.ToString() == ItemName)
		{
			if (slot.Amount <= StackSize)
				LeastIndex = index;
		}
		index++;
	}
	if(LeastIndex != -1)
		Inventory->UsePotionSlot(LeastIndex);
}

void AUserCharacter::SetHitFalse()
{
	if (AnimInstance)
	{
		AnimInstance->SetIsHit(false);
		GetWorldTimerManager().ClearTimer(HitHandle);
	}
}

void AUserCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUserCharacter, MeshPath);
	DOREPLIFETIME(AUserCharacter, ClassType);
	DOREPLIFETIME(AUserCharacter, MyWeapon);
	DOREPLIFETIME(AUserCharacter, Inventory);
	DOREPLIFETIME(AUserCharacter, QuickSlot);
}

void AUserCharacter::HideChatBalloon()
{
	if(ChatBalloon)
		ChatBalloon->SetRenderOpacity(0.f);
}

float AUserCharacter::CalculateHitDirectionAngle(const FVector& AttackerLocation)
{
	FVector VictimLocation = GetActorLocation();

	FVector HitDirection = VictimLocation - AttackerLocation;
	HitDirection.Normalize();

	FVector ForwardVector = GetActorForwardVector();

	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(HitDirection);
	FVector LocalHitDirection = UKismetMathLibrary::InverseTransformDirection(GetActorTransform(), HitDirection);

	float HitAngle = FMath::RadiansToDegrees(FMath::Atan2(LocalHitDirection.Y, LocalHitDirection.X));

	return HitAngle;
}

void AUserCharacter::UserDied()
{
	IsDead = true;

	if (HUDWidget)
		HUDWidget->ShowRespawn(this);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->bPauseAnims = true;

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
}

void AUserCharacter::UserReset()
{
	IsDead = false;

	if(AnimInstance)
		AnimInstance->WakeUpPlayAM();

	if (HUDWidget)

		HUDWidget->RemoveRespawn();

	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->bPauseAnims = false;
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	LoadCharacterData();
}

void AUserCharacter::SetWidget()
{
	if (HUDWidget && !HUDWidget->IsInViewport())
	{
		HUDWidget->AddToViewport();
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		EnableInput(PlayerController);
	}
}

void AUserCharacter::RemoveWidget()
{
	if (HUDWidget && HUDWidget->IsInViewport())
	{
		HUDWidget->RemoveFromParent();
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
}



