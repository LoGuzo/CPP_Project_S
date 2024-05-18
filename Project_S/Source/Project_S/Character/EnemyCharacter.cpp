// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "Project_S/AnimInstance/MonsterAnimInstance.h"
#include "Project_S/Controllers/EnemyAIController.h"
#include "Project_S/Controllers/AggressiveAIController.h"
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
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
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

	SetMesh();

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnlyHpBar->SetRenderOpacity(1.f);
	if (Stat->GetHp() <= 0)
	{
		UseSkill("Mutant_Die");
	}
	return DamageAmount;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Stat->SetLevel(1);
	NowAIController = Cast<AAggressiveAIController>(GetController());
	SaveLocation = GetActorLocation();
}

void AEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (NowPattern.IsValid())
	{
		NowPattern.Reset();
	}
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

	AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->SetMonster(this);
	}
}

void AEnemyCharacter::SetMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("SkeletalMesh'/Game/Mannequin/Monster/Character/Mesh/Mutant_UE.Mutant_UE'"));
	if (SK_WEAPON.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_WEAPON.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	FVector MeshLocation = FVector(-20.f, 0.f, -90.f);
	FRotator MeshRotator = FRotator(0.f, -90.f, 0.f);
	GetMesh()->SetRelativeLocationAndRotation(MeshLocation, MeshRotator);
}

void AEnemyCharacter::UseSkill(FString _SkillName)
{
	const auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		const auto PatternData = StaticCastSharedPtr<FMonsterPattern>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_MonsterPattern)->GetMyData(_SkillName));
		NowPattern = PatternData;
		AnimInstance->PlaySome(PatternData);
	}
}

void AEnemyCharacter::DiedEnemy()
{	
	GetCharacterMovement()->GravityScale = 0.f;
	GetController()->UnPossess();
	GetMesh()->SetSkeletalMesh(nullptr);
	OnlyHpBar->SetRenderOpacity(0.f);
	SetActorLocation(FVector(SaveLocation.X, SaveLocation.Y, SaveLocation.Z + 1000.f));
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEnemyCharacter::ResetStat, 10.f, false);
}

void AEnemyCharacter::ResetStat()
{
	GetMesh()->SetEnableGravity(true);
	Stat->SetHp(Stat->GetMaxHp());
	SetActorLocation(SaveLocation);
	GetCharacterMovement()->GravityScale = 1.f;
	SetMesh();
	NowAIController->Possess(this);
}

