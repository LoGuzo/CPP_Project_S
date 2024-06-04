// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Missle.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
}

void AProjectile_Missle::BeginPlay()
{
	Super::BeginPlay();
	if (NiagaraSystem)
	{
		//NiagaraComponent->SetAsset(NiagaraSystem);
		//NiagaraComponent->ActivateSystem();
	}
}

void AProjectile_Missle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Target)
	{
		FVector Direction = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
	}
}

void AProjectile_Missle::SetTarget(AActor* TargetActor)
{
	Target = TargetActor;
	if (Target)
	{
		ProjectileMovementComponent->Activate();
	}
}