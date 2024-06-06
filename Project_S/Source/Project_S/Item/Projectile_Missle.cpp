// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Missle.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Project_S/Character/FirstCharacter.h"

AProjectile_Missle::AProjectile_Missle()
{
	ProjectileMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Projectile"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->CastShadow = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackP(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (AttackP.Succeeded())
	{
		HitParticleEffect = AttackP.Object;
	}

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetRelativeLocation(FVector(-230.0f, 0.f, 0.f));
	SetActorRelativeRotation(FRotator(-10.f,0.f, 0.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ProjetileM(TEXT("SkeletalMesh'/Game/VigilanteContent/Projectiles/West_Missile_AGM65/SK_West_Missile_AGM65.SK_West_Missile_AGM65'"));
	if(ProjetileM.Succeeded())
	{
		ProjectileMesh->SetSkeletalMesh(ProjetileM.Object);
		ProjectileMesh->SetRelativeLocation(FVector(-120.f, 0.f, 0.f));
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>Niagara(TEXT("NiagaraSystem'/Game/VigilanteContent/Projectiles/West_Missile_AGM65/FX/NS_West_Missile_AGM65.NS_West_Missile_AGM65'"));
	if (Niagara.Succeeded())
	{
		NiagaraSystem = Niagara.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundWave> SoundObject(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
	if (SoundObject.Succeeded())
	{
		ParticleSound = SoundObject.Object;
	}
	StartMoving = false;

	SetActorHiddenInGame(true);
}

void AProjectile_Missle::BeginPlay()
{
	Super::BeginPlay();
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AProjectile_Missle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StartMoving)
	{
		MoveTowardsTarget(DeltaTime);
		RotateTowardsTarget(DeltaTime);
	}
}

void AProjectile_Missle::SetTarget(FVector _Location, FVector _Target)
{
	Target = _Target;
	if (Target.Size() > 0)
	{
		SetActorLocation(_Location);
		SetActorRotation(Owner->GetActorRotation());
		StartMoving = true;
		if (NiagaraSystem)
		{
			NiagaraComponent->SetAsset(NiagaraSystem);
		}
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
		FVector Direction = (Target - GetActorLocation()).GetSafeNormal();
		ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
		ProjectileMovementComponent->Activate();
	}
}

void AProjectile_Missle::MoveTowardsTarget(float DeltaTime)
{
	if (FVector::Dist(GetActorLocation(), Target) <= 10.0f) // 목표 지점에 거의 도착했을 때
	{
		// 폭발 효과를 트리거
		Explode();
	}
}

void AProjectile_Missle::RotateTowardsTarget(float DeltaTime)
{
	FVector Direction = (Target - GetActorLocation()).GetSafeNormal();
	FRotator TargetRotation = Direction.Rotation();
	FRotator CurrentRotation = GetActorRotation();

	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
	SetActorRotation(NewRotation);
}

void AProjectile_Missle::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleEffect, GetActorLocation());
	ScopeAttackCheck(300);
	if (ParticleSound && AudioComponent)
	{
		AudioComponent->SetSound(ParticleSound);
		AudioComponent->Play();
	}
	StartMoving = false;
	NiagaraComponent->SetAsset(nullptr);
	ProjectileMovementComponent->StopMovementImmediately();
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}