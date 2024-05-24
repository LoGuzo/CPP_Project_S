// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "Project_S/AnimInstance/MonsterAnimInstance.h"
#include "Project_S/Controllers/EnemyAIController.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Widget/OnlyHpBar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

AEnemyCharacter::AEnemyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
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
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnlyHpBar->SetRenderOpacity(1.f);
	AFirstCharacter* User = Cast<AFirstCharacter>(DamageCauser);
	if (Stat->GetHp() <= 0 && !IsDead)
	{
		IsDead = true;
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
	}
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
				Stat->SetHp(LoadData.Pin()->MaxHp);
				Stat->SetMaxHp(LoadData.Pin()->MaxHp);
				Stat->SetMp(LoadData.Pin()->MaxMp);
				Stat->SetMaxMp(LoadData.Pin()->MaxMp);
				Stat->SetMaxExp(LoadData.Pin()->MaxExp);
				Stat->SetExp(0);
				Stat->SetAttack(LoadData.Pin()->Attack);
				Stat->SetArmor(LoadData.Pin()->Armor);
				Skill->SetSlots(LoadData.Pin()->MonsterSkill);
				SetMesh(LoadData.Pin()->MonsterMesh,LoadData.Pin()->MonsterMaterial);
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

void AEnemyCharacter::SetEtc()
{
	NowAIController = Cast<AEnemyAIController>(GetController());
	SaveLocation = GetActorLocation();
}

void AEnemyCharacter::UseSkill(FString _SkillName)
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
	NowAIController->UnPossess();
	GetCharacterMovement()->GravityScale = 0.f;
	GetMesh()->SetSkeletalMesh(nullptr);
	OnlyHpBar->SetRenderOpacity(0.f);
	SetActorLocation(FVector(SaveLocation.X, SaveLocation.Y, SaveLocation.Z + 5000.f));
	if (IsReadySpawn)
	{
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEnemyCharacter::ResetStat, 10.f, false);
	}
}

void AEnemyCharacter::ResetStat()
{
	IsDead = false;
	NowAIController->IsDead = false;
	IsReadySpawn = false;
	GetMesh()->SetEnableGravity(true);
	LoadCharacterData();
	SetActorLocation(SaveLocation);
	GetCharacterMovement()->GravityScale = 1.f;
	UseSkill(Skill->GetSlot(2).ItemName.ToString());
	NowAIController->Possess(this);
}

