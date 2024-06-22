// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Project_S/AnimInstance/MonsterAnimInstance.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Controllers/EnemyAIController.h"
#include "Project_S/Item/Projectile_Missle.h"
#include "Project_S/Widget/W_BossHp.h"

ABossCharacter::ABossCharacter()
{
	SetBossMesh();
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_BossHP.WBP_BossHp_C'"));
	if (UW.Succeeded())
	{
		U_BossHp = UW.Class;
	}
	static ConstructorHelpers::FObjectFinder<USoundWave> SoundObject(TEXT("SoundWave'/Game/Ancient_Golem/Sound/metal-hit-91-200421.metal-hit-91-200421'"));
	if (SoundObject.Succeeded())
	{
		ParticleSound = SoundObject.Object;
	}
	CntMissile = 0;
	ProjectileClass = AProjectile_Missle::StaticClass();
}

void ABossCharacter::SetBossMesh()
{
	//SetActorScale3D(FVector(5.f, 5.f, 5.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	FVector MeshLocation = FVector(0.f, 0.f, -300.f);
	FRotator MeshRotator = FRotator(0.f, -90.f, 0.f);
	GetMesh()->SetRelativeLocationAndRotation(MeshLocation, MeshRotator);
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));
	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/Ancient_Golem/Demo/Boss_AnimBP.Boss_AnimBP_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));
	if (MainAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
	}
	HeadWheel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadWheel"));
	Drill = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drill"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WheelAsset(TEXT("SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Head_Wheel.SK_Ancient_Golem_Head_Wheel'"));
	if (WheelAsset.Succeeded())
	{
		HeadWheel->SetSkeletalMesh(WheelAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DrillAsset(TEXT("SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels'"));
	if (DrillAsset.Succeeded())
	{
		Drill->SetSkeletalMesh(DrillAsset.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> WheelAnimAsset(TEXT("AnimBlueprint'/Game/Ancient_Golem/Animation/SK_Ancient_Golem_Head_Wheel_Skeleton_AnimBlueprint.SK_Ancient_Golem_Head_Wheel_Skeleton_AnimBlueprint_C'"));
	if (WheelAnimAsset.Succeeded())
	{
		HeadWheel->SetAnimInstanceClass(WheelAnimAsset.Class);
	}
	HeadWheel->SetupAttachment(GetMesh(), TEXT("headSocket"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> DrillAnimAsset(TEXT("AnimBlueprint'/Game/Ancient_Golem/Animation/SK_Ancient_Golem_Moving_Wheels_Skeleton_AnimBlueprint.SK_Ancient_Golem_Moving_Wheels_Skeleton_AnimBlueprint_C'"));
	if (DrillAnimAsset.Succeeded())
	{
		Drill->SetAnimInstanceClass(DrillAnimAsset.Class);
	}
	Drill->SetupAttachment(GetMesh(), TEXT("spine_03Socket"));
	BossDied = false;
}

void ABossCharacter::AnyMove()
{
	SetActorLocation(NowAIController->GetUser()->GetActorLocation());
}

void ABossCharacter::LoadCharacterData()
{
	Super::LoadCharacterData();
	if (W_BossHp)
	{
		if (Stat)
		{
			W_BossHp->SetTxtName(Stat->GetLevel(), GetCharID());
		}
	}
	SetWidget();
	SetState(true);
}
void ABossCharacter::SetWidget()
{
	if (W_BossHp && !W_BossHp->IsInViewport())
	{
		W_BossHp->AddToViewport();
	}
}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Stat) {
		if (Stat->GetHp() <= 0)
		{
			OnDied.Broadcast();
			GetWorldTimerManager().SetTimer(RemoveWidgetHandle, this, &ABossCharacter::RemoveWidget, 10.f, false);
		}
	}
	return DamageAmount;
}

void ABossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	W_BossHp = CreateWidget<UW_BossHp>(GetWorld(), U_BossHp);
	if (W_BossHp)
	{
		if (Stat)
		{
			W_BossHp->BindHp(Stat);
		}
	}
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	Make_Projectile();
}

void ABossCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(RemoveWidgetHandle);
}

void ABossCharacter::Make_Projectile()
{
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			for (int32 i=0; i < 5; i++)
			{
				AProjectile_Missle* Missle = World->SpawnActor<AProjectile_Missle>(ProjectileClass);
				Missle->SetProjectileOwner(this);
				MyProjectiles.Emplace(Missle);
			}
		}
	}
}

void ABossCharacter::Set_Projectile()
{
	if (!ProjectileClass) return;
	if (!Target) return;
	if (CntMissile > 4) CntMissile = 0;

	auto TargetCharacter = Cast<ACharacter>(Target);
	FVector RealTarget = TargetCharacter->GetActorLocation() - FVector(0.0f, 0.0f, TargetCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	MyProjectiles[CntMissile]->SetTarget(SetMissleLocation(), RealTarget);
	CntMissile++;
}

FVector ABossCharacter::SetMissleLocation()
{
	FVector BossLocation = GetActorLocation() + FVector(0.f, 0.f, 300.f);
	FRotator BossRotation = GetActorRotation();
	FVector BossBackward = -BossRotation.Vector();
	FRotator RotationOffset(0.f, -90.f, 0.f);
	FVector ForwardVector = RotationOffset.RotateVector(GetActorForwardVector());
	float Radius = 600.f;
	float AngleStep = 180.f / 4;
	float Angle = AngleStep * CntMissile * PI / 180.f;
	FVector SpawnOffset = FVector(-FMath::Cos(Angle) * ForwardVector.X, -FMath::Cos(Angle) * ForwardVector.Y, FMath::Sin(Angle)); // 반원 형태의 오프셋 계산
	FVector SpawnLocation = BossLocation + SpawnOffset * Radius; // 미사일이 소환될 위치 계산

	return SpawnLocation;
}
void ABossCharacter::RemoveWidget()
{
	if (W_BossHp && W_BossHp->IsInViewport())
	{
		W_BossHp->RemoveFromViewport();
	}
}

void ABossCharacter::StartAISearch()
{
	if (NowAIController)
	{
		NowAIController->StartAISearch();
	}
}
