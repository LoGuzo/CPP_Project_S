// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project_S/AnimInstance/MonsterAnimInstance.h"
#include "Project_S/Controllers/EnemyAIController.h"
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
	MyCharType = E_CharacterType::E_Monster;
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_OnlyHpBar.WBP_OnlyHpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 500.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/Mannequin/Monster/Animations/BP_MutantAnimInstance.BP_MutantAnimInstance_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}
	IsDead = false;
	IsReadySpawn = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetActorHiddenInGame(true);
}

void AEnemyCharacter::SetState(bool NowState)
{
	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
	SetActorTickEnabled(NowState);
	if (NowState)
		NowAIController->Possess(this);
	else
		NowAIController->UnPossess();
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Type != E_MonsterType::E_LastBoss && Type != E_MonsterType::E_MiddleBoss)
		OnlyHpBar->SetRenderOpacity(1.f);
	AFirstCharacter* User = Cast<AFirstCharacter>(DamageCauser);
	if (Stat->GetHp() <= 0)
	{
		NowAIController->IsDead = true;
		IsReadySpawn = true;
		UseSkill(Skill->GetSlot(1).ItemName.ToString());
		User->GetStatCom()->SetExp(User->GetStatCom()->GetExp() + Stat->GetMaxExp());
	}
	return DamageAmount;
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

void AEnemyCharacter::SetMesh(TSoftObjectPtr<UStreamableRenderAsset> _MonsterMesh, TSoftObjectPtr<UMaterialInterface> _MonsterMaterial)
{
	USkeletalMesh* MeshPath = Cast<USkeletalMesh>(_MonsterMesh.LoadSynchronous());
	if (MeshPath)
	{
		GetMesh()->SetSkeletalMesh(MeshPath);
		UMaterialInstance* MaterialPath = Cast<UMaterialInstance>(_MonsterMaterial.LoadSynchronous());
		if (MaterialPath)
		{
			MyMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialPath, this);
			GetMesh()->SetMaterial(0, MyMaterialInstanceDynamic);
		}
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		FVector MeshLocation = FVector(-20.f, 0.f, -90.f);
		FRotator MeshRotator = FRotator(0.f, -90.f, 0.f);
		GetMesh()->SetRelativeLocationAndRotation(MeshLocation, MeshRotator);
		HpBar->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("HpBar"));
	}
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
						AA_Item* DropItem = GetWorld()->SpawnActor<AA_Item>(ItemData.Get()->ItemClass, SpawnLocation, FRotator::ZeroRotator);
						DropItem->SetItem(Item[i]);
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
				if (!GetMesh()->SkeletalMesh)
				{
					SetMesh(LoadData.Pin()->MonsterMesh, LoadData.Pin()->MonsterMaterial);
				}
			}
		}
	}
	AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->SetMonster(this);
	}
	UseSkill(Skill->GetSlot(2).ItemName.ToString());
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

void AEnemyCharacter::UseSkill(const FString& _SkillName)
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
	GetCharacterMovement()->GravityScale = 0.f;
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
	GetMesh()->SetEnableGravity(true);
	SetState(true);
	LoadCharacterData();
	SetActorLocation(SaveLocation);
	GetCharacterMovement()->GravityScale = 1.f;
}


