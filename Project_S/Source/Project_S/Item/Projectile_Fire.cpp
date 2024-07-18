// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Fire.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile_Fire::AProjectile_Fire()
{
	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticle"));
	ProjectileParticle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackP(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_Circle_ChargeUp_Fire.P_Circle_ChargeUp_Fire'"));
	if (AttackP.Succeeded())
	{
		ParticleEffect = AttackP.Object;
	}
}

void AProjectile_Fire::SetProjectile()
{
	if (ParticleEffect)
	{
		ProjectileParticle->SetTemplate(ParticleEffect);
		ProjectileParticle->Activate();
	}
}

void AProjectile_Fire::Explode()
{
	ScopeAttackCheck(300);
	SetParticle();
	ProjectileMovementComponent->StopMovementImmediately();
	Destroy();
}