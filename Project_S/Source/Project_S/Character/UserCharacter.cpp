// Fill out your copyright notice in the Description page of Project Settings.


#include "UserCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Project_S/UserCameraShake.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/MappingClass.h"
#include "Project_S/AnimInstance/UserAnimInstance.h"
#include "Project_S/Component/C_EqiupComponent.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include "Project_S/Component/C_QuickSlotComponent.h"
#include "Project_S/Item/WeaponActor.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Widget/S_CharacterWidget.h"
#include "Project_S/Widget/InventoryMenu.h"
#include "Project_S/Widget/W_Inventory.h"

AUserCharacter::AUserCharacter()
{
	MyCharType = E_CharacterType::E_User;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

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

	Inventory = CreateDefaultSubobject<UC_InventoryComponent>(TEXT("INVENTORY"));
	Equip = CreateDefaultSubobject<UC_EqiupComponent>(TEXT("EQUIP"));
	QuickSlot = CreateDefaultSubobject<UC_QuickSlotComponent>(TEXT("QUICK"));
	static ConstructorHelpers::FClassFinder<US_CharacterWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_UserWidget.WBP_UserWidget_C'"));
	if (UW.Succeeded())
	{
		CharacterUI = UW.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserCameraShake>CS(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/BP_UserCameraShake.BP_UserCameraShake_C'"));
	if (CS.Succeeded())
	{
		TCameraShake = CS.Class;
	}

	//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(TCameraShake);

	bIsFlipFlopInventoryActive = false;
	bIsFlipFlopEquipmentActive = false;
	bIsFlipFlopSkillWidgetActive = false;
	IsAttacking = false;
	SetCharID("LogH");
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
	PlayerInputComponent->BindAction("SkillWidget", IE_Pressed, this, &AUserCharacter::OnSkillWidgetKeyPressed);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AUserCharacter::PickUpItem);
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
	MappingClass* CharacterTypeMapping = new MappingClass();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		ClassData = StaticCastSharedPtr<FCharacterClass>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_CharClassData)->GetMyData(CharacterTypeMapping->GetCharacterDescription(_ClassType)));
		if (ClassData.IsValid())
		{
			USkeletalMesh* MeshPath = ClassData.Pin()->ClassMesh.LoadSynchronous();
			if (MeshPath)
			{
				GetMesh()->SetSkeletalMesh(MeshPath);
				GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
				GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
				GetMesh()->SetAnimInstanceClass(ClassData.Pin()->ClassAnim.LoadSynchronous());
				GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
			}
		}
		AnimInstance = Cast<UUserAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->SetPlayer(this);
			AnimInstance->OnAttackHit.AddUObject(this, &AUserCharacter::AttackCheck);
			AnimInstance->OnMontageEnded.AddDynamic(this, &AUserCharacter::OnAttackMontageEnd);
		}
	}
}
void AUserCharacter::BeginPlay()
{
	Super::BeginPlay();
	LoadCharacterData();
	SaveLocation = GetActorLocation();
}

void AUserCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveCharacterData();
	if (LoadData.IsValid())
	{
		LoadData.Reset();
	}
	if (NowSkill.IsValid())
	{
		NowSkill.Reset();
	}
	if (ClassData.IsValid())
	{
		ClassData.Reset();
	}
	GetWorldTimerManager().ClearTimer(UnusedHandle);
}

float AUserCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Stat->GetHp() <= 0)
	{
		//AnimInstance->PlaySome();
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
	{
		HUDWidget = CreateWidget<US_CharacterWidget>(GetWorld(), CharacterUI);
		if (HUDWidget)
		{
			HUDWidget->BindLvl(Stat);
			HUDWidget->BindHp(Stat);
			HUDWidget->BindMp(Stat);
			HUDWidget->BindExp(Stat);
			HUDWidget->ShowQuick(QuickSlot);
			HUDWidget->AddToViewport();
		}
	}
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
		if (GetCharID() != "") {
			MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->SetMyData(GetCharID(), &NowCharData);
		}
	}
}

void AUserCharacter::LoadCharacterData()
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
				{
					SetMyWeapon(slot.ItemClass);
				}
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

void AUserCharacter::PickUpItem()
{
	if (GetCurItem() != nullptr) {
		GetCurItem()->GetC_ItemComponent()->Interact(this);
		UpdateInventory();
	}
}

void AUserCharacter::TimelineProgress(float _Value)
{
	GetMesh()->SetRelativeRotation(FRotator(BeforeRot.Pitch, FMath::Lerp(BeforeRot.Yaw, BeforeRot.Yaw + float(360 * 12), _Value), BeforeRot.Roll));
}

void AUserCharacter::SetMyWeapon(const TSubclassOf<class AA_Item>_MyWeapon)
{
	// UserClass
	FName WeaponSocket(TEXT("r_hand_sword"));
	MyWeapon = GetWorld()->SpawnActor<AWeaponActor>(_MyWeapon);
	if (nullptr != MyWeapon) {
		MyWeapon->GetBoxCollision()->SetCollisionProfileName(TEXT("NoCollision"));
		MyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		MyWeapon->SetOwner(this);
	}
	if (AnimInstance)
	{
		AnimInstance->SetHaveWeapon(true);
	}
}

void AUserCharacter::RemoveMyWeapon()
{
	if (MyWeapon != nullptr)
	{
		MyWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		MyWeapon->SetOwner(nullptr);
		MyWeapon->Destroy();
		MyWeapon = nullptr;
	}
	if (AnimInstance)
	{
		AnimInstance->SetHaveWeapon(false);
	}
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
	AnimInstance->OnHandSwordPlayAM();
	AnimInstance->JumpToSection(AttackIndex);
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
			{
				UseSkill(QuickSlot->GetSkillSlot(0));
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Two))
		{
			if (QuickSlot->GetSkillSlot(1) != "None")
			{
				UseSkill(QuickSlot->GetSkillSlot(1));
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Three))
		{
			if (QuickSlot->GetSkillSlot(2) != "None")
			{
				UseSkill(QuickSlot->GetSkillSlot(2));
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Four))
		{
			if (QuickSlot->GetSkillSlot(3) != "None")
			{
				UseSkill(QuickSlot->GetSkillSlot(3));
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Five))
		{
			if (QuickSlot->GetSkillSlot(4) != "None")
			{
				UseSkill(QuickSlot->GetSkillSlot(4));
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Six))
		{
			if (Stat->GetHp() <= Stat->GetMaxHp())
			{
				if (QuickSlot->GetPotionSlot(0) != "None")
				{
					QuickSlot->UsePotionSlot(0);
					Inventory->UsePotionSlot(QuickSlot->BindTarget.FindRef(0));
					QuickSlot->OnQuickUpdated.Broadcast();
					Inventory->OnInventoryUpdated.Broadcast();
				}
			}
		}
		if (PlayerController->IsInputKeyDown(EKeys::Seven))
		{
			if (Stat->GetMp() <= Stat->GetMaxMp())
			{
				if (QuickSlot->GetPotionSlot(1) != "None")
				{
					QuickSlot->UsePotionSlot(1);
					Inventory->UsePotionSlot(QuickSlot->BindTarget.FindRef(1));
					QuickSlot->OnQuickUpdated.Broadcast();
					Inventory->OnInventoryUpdated.Broadcast();
				}
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

void AUserCharacter::UpdateInventory()
{
	if (IsValid(HUDWidget->GetInvetoryWidget()))
	{
		HUDWidget->GetInvetoryWidget()->WBP_Inventory->ShowInventory(Inventory);
	}
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

void AUserCharacter::Dash()
{
	// Get the last input vector (movement direction)
	FVector LastInputVector = GetCharacterMovement()->GetLastInputVector();
	if (LastInputVector.IsNearlyZero())
	{
		// If no movement input, dash in the forward direction
		LastInputVector = GetActorForwardVector();
	}
	else
	{
		// Normalize the input vector to get the direction
		LastInputVector = LastInputVector.GetSafeNormal();
	}
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
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AUserCharacter::ResetDash, 0.1f, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
}

void AUserCharacter::ResetDash()
{
	AnimInstance->SetOnDash(false);
}

void AUserCharacter::UseSkill(FString _SkillName)
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





