// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Project_S/AnimInstance/MonsterAnimInstance.h"
#include "Project_S/Controllers/EnemyAIController.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Item/A_Item.h"
#include "Project_S/Widget/OnlyHpBar.h"
#include "Project_S/Item/RedPotionActor.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	HpBar->SetupAttachment(RootComponent);
	MyCharType = E_CharacterType::E_Monster;
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_OnlyHpBar.WBP_OnlyHpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 500.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(-20.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/Mannequin/Monster/Animations/BP_MutantAnimInstance.BP_MutantAnimInstance_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}
	IsDead = false;
	IsReadySpawn = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->GravityScale = 0.f;
	SetActorHiddenInGame(true);
}

void AEnemyCharacter::SetState(bool NowState)
{
	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
	SetActorTickEnabled(NowState);
	if (NowState)
	{
		GetCharacterMovement()->GravityScale = 1.f;
		NowAIController->Possess(this);
	}
	else
	{
		GetCharacterMovement()->GravityScale = 0.f;
		if (HasAuthority())
			NowAIController->UnPossess();
	}
	if (Skill->GetSlots().Num() > 2 && Type != E_MonsterType::E_LastBoss)
		UseSkill(Skill->GetSlot(2).ItemName.ToString());
}

void AEnemyCharacter::SetMonsterID(int32 _MonsterID)
{
	MonsterID = _MonsterID;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Type != E_MonsterType::E_LastBoss)
	{
		SyncHpBar(EventInstigator);
	}

	AFirstCharacter* User = Cast<AFirstCharacter>(DamageCauser);
	if (Stat->GetHp() <= 0)
	{
		NowAIController->IsDead = true;
		IsReadySpawn = true;
		UseSkill(Skill->GetSlot(1).ItemName.ToString());
		User->GetStatCom()->SetExp(User->GetStatCom()->GetExp() + Stat->GetMaxExp());
		OnUpdateQuest.Broadcast(MonsterID);
	}
	return DamageAmount;
}

void AEnemyCharacter::ShowHpBar()
{
	if (OnlyHpBar)
	{
		OnlyHpBar->SetRenderOpacity(1.f);
	}
}

void AEnemyCharacter::SyncHpBar(AController* PlayerController)
{
	AUserPlayerController* UserPlayerController = Cast<AUserPlayerController>(PlayerController);
	if (UserPlayerController)
	{
		UserPlayerController->SyncEnemyHpBar(this);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (NowPattern.IsValid())
		NowPattern.Reset();
	if (LoadData.IsValid())
		LoadData.Reset();

	GetWorldTimerManager().ClearTimer(UnusedHandle);
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HpBar->InitWidget();

	OnlyHpBar = Cast<UOnlyHpBar>(HpBar->GetUserWidgetObject());
	if (OnlyHpBar)
	{
		OnlyHpBar->BindHp(Stat);
		OnlyHpBar->SetRenderOpacity(0.f);
	}
}

void AEnemyCharacter::SetMesh(const TSoftObjectPtr<UStreamableRenderAsset>& _MonsterMesh, const TSoftObjectPtr<UMaterialInterface>& _MonsterMaterial)
{
	if (HasAuthority())
	{
		MeshPath = Cast<USkeletalMesh>(_MonsterMesh.LoadSynchronous());
		MaterialPath = Cast<UMaterialInstance>(_MonsterMaterial.LoadSynchronous());

		OnRep_MeshPath();
		OnRep_MaterialPath();
	}
}

void AEnemyCharacter::OnRep_MeshPath()
{
	if (MeshPath && GetMesh())
	{
		GetMesh()->SetSkeletalMesh(MeshPath);
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		HpBar->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("HpBar"));
	}

	AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->SetMonster(this);
	}
}

void AEnemyCharacter::OnRep_MaterialPath()
{
	if (MaterialPath && GetMesh())
	{
		MyMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialPath, this);
		GetMesh()->SetMaterial(0, MyMaterialInstanceDynamic);
	}
}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyCharacter, MeshPath);
	DOREPLIFETIME(AEnemyCharacter, MaterialPath);
}

void AEnemyCharacter::DropItem()
{
	for (int i = 0; i < Item.Num(); i++)
	{
		auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (MyGameInstance)
		{
			if (Item[i] != "") {
				auto ItemData = StaticCastSharedPtr<FS_Item>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetMyData(Item[i]));
				if (ItemData.IsValid())
				{
					if (RandRange(0.f, 100.f) < ItemData.Get()->DropChance)
					{
						FVector RandomOffset = FVector(RandRange(-100.0f, 100.0f), RandRange(-100.0f, 100.0f), 0.0f);
						FVector SpawnLocation = GetActorLocation() + RandomOffset;
						class AA_Item* DropItems = GetWorld()->SpawnActor<AA_Item>(ItemData.Get()->ItemClass, SpawnLocation, FRotator::ZeroRotator);
						DropItems->SetItem(Item[i]);
					}
				}
			}
		}
	}
}

void AEnemyCharacter::LoadCharacterData()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (GetCharID() != "") {
			LoadData = StaticCastSharedPtr<FMonsterData>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_MonsterData)->GetMyData(GetCharID()));
			if (LoadData.IsValid())
			{
				Stat->SetMonsterLevel(LoadData.Pin()->Level);
				Stat->SetMaxHp(LoadData.Pin()->MaxHp);
				Stat->SetHp(LoadData.Pin()->MaxHp);
				Stat->SetMaxMp(LoadData.Pin()->MaxMp);
				Stat->SetMp(LoadData.Pin()->MaxMp);
				Stat->SetMaxExp(LoadData.Pin()->MaxExp);
				Stat->SetExp(0);
				Stat->SetAttack(LoadData.Pin()->Attack);
				Stat->SetArmor(LoadData.Pin()->Armor);
				Type = LoadData.Pin()->Type;
				Item = LoadData.Pin()->DropItem;
				Skill->SetSlots(LoadData.Pin()->MonsterSkill);
				SetMesh(LoadData.Pin()->MonsterMesh, LoadData.Pin()->MonsterMaterial);
			}
		}
	}
}

void AEnemyCharacter::SetTarget(AUserCharacter* _Target)
{
	Target = _Target;
}

void AEnemyCharacter::SetEtc()
{
	NowAIController = Cast<AEnemyAIController>(GetController());
	SaveLocation = GetActorLocation();
}

void AEnemyCharacter::Multi_UseSkill(const FString& SkillName)
{
	Super::Multi_UseSkill(SkillName);
}

void AEnemyCharacter::Multi_UseSkill_Implementation(const FString& _SkillName)
{
	const auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		const auto PatternData = StaticCastSharedPtr<FMonsterPattern>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_MonsterPattern)->GetMyData(_SkillName));
		NowPattern = PatternData;
		if (AnimInstance)
		{
			AnimInstance->PlaySome(PatternData);
		}
	}
}

void AEnemyCharacter::DiedEnemy()
{
	OnlyHpBar->SetRenderOpacity(0.f);
	IsAttacking = false;
	DropItem();
	SetActorLocation(FVector(SaveLocation.X, SaveLocation.Y, SaveLocation.Z + 1000.f));
	SetState(false);
	if (Type != E_MonsterType::E_LastBoss)
	{
		if (IsReadySpawn)
		{
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEnemyCharacter::ResetStat, 10.f, false);
		}
	}
}

void AEnemyCharacter::ResetStat()
{
	IsDead = false;
	NowAIController->IsDead = false;
	IsReadySpawn = false;
	SetActorLocation(SaveLocation);
	SetState(true);
	LoadCharacterData();
}


