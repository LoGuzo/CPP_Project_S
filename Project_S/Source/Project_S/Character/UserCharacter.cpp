// Fill out your copyright notice in the Description page of Project Settings.


#include "UserCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Project_S/Widget/S_CharacterWidget.h"
#include "Project_S/Item/WeaponActor.h"
#include "Project_S/Widget/InventoryMenu.h"
#include "Project_S/Widget/W_Inventory.h"
#include "Project_S/Component/C_EqiupComponent.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Kismet/GameplayStatics.h"

AUserCharacter::AUserCharacter()
{
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
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Inventory = CreateDefaultSubobject<UC_InventoryComponent>(TEXT("INVENTORY"));
	Equip = CreateDefaultSubobject<UC_EqiupComponent>(TEXT("EQUIP"));
	static ConstructorHelpers::FClassFinder<US_CharacterWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_UserWidget.WBP_UserWidget_C'"));
	if (UW.Succeeded())
	{
		CharacterUI = UW.Class;
	}
	bIsFlipFlopInventoryActive = false;
	bIsFlipFlopEquipmentActive = false;

	SetCharID("LogH");
	NowCharData.CharID = GetCharID();
}

void AUserCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUserCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUserCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AUserCharacter::Attack);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AUserCharacter::OnInventoryKeyPressed);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AUserCharacter::OnEquipmentKeyPressed);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AUserCharacter::PickUpItem);
}

void AUserCharacter::BeginPlay()
{
	Super::BeginPlay();
	LoadCharacterData();
	Stat->SetExp(10);
}

void AUserCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveCharacterData(GetCharID(),NowCharData);
}

void AUserCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CharacterUI)
	{
		HUDWidget = CreateWidget<US_CharacterWidget>(GetWorld(), CharacterUI);
		if (HUDWidget)
		{
			HUDWidget->BindHp(Stat);
			HUDWidget->BindMp(Stat);
			HUDWidget->BindExp(Stat);
			HUDWidget->AddToViewport();
		}
	}
}

void AUserCharacter::SaveCharacterData(FString _RowName, struct FMyCharacterData _NewData)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (GetCharID() != "") {
			MyGameInstance->MyDataManager.FindRef("MyCharData")->SetMyData(_RowName, _NewData);
		}
	}
}

void AUserCharacter::LoadCharacterData()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (GetCharID() != "") {
			auto LoadData = static_cast<FMyCharacterData*>(MyGameInstance->MyDataManager.FindRef("MyCharData")->GetMyData(GetCharID()));
			if (LoadData)
			{
				NowCharData.Level = LoadData->Level;
				Stat->SetLevel(LoadData->Level);
				NowCharData.MyEquip = LoadData->MyEquip;
				Equip->SetSlots(LoadData->MyEquip);
				NowCharData.MyInventory = LoadData->MyInventory;
				Inventory->SetSlots(LoadData->MyInventory);
			}

		}
	}
	for (const FS_Slot& slot : NowCharData.MyEquip)
	{
		if (slot.ItemClass)
		{
			SetMyWeapon(slot.ItemClass);
		}
	}
}

void AUserCharacter::SetNowLevelData(int32 _Level)
{
	NowCharData.Level = _Level;
}

void AUserCharacter::SetNowEquipData(const TArray<struct FS_Slot>&_MyEquip)
{
	NowCharData.MyEquip = _MyEquip;
}

void AUserCharacter::SetNowInvenData(const TArray<struct FS_Slot>&_MyInven)
{
	NowCharData.MyInventory = _MyInven;
}

void AUserCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUserCharacter::MoveRight(float Value)
{
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

void AUserCharacter::Tick(float DeltaTime)
{
}

void AUserCharacter::PickUpItem()
{
	if (GetCurItem() != nullptr) {
		GetCurItem()->GetC_ItemComponent()->Interact(this);
		UpdateInventory();
	}
}

void AUserCharacter::SetMyWeapon(TSubclassOf<class AA_Item>_MyWeapon)
{
	// UserClass
	FName WeaponSocket(TEXT("r_hand_sword"));
	MyWeapon = GetWorld()->SpawnActor<AWeaponActor>(_MyWeapon);
	if (nullptr != MyWeapon) {
		MyWeapon->GetBoxCollision()->SetCollisionProfileName(TEXT("NoCollision"));
		MyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		MyWeapon->SetOwner(this);
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
}

void AUserCharacter::Attack()
{
	if (nullptr != MyWeapon)
		MyWeapon->AttackCheck(this);
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
