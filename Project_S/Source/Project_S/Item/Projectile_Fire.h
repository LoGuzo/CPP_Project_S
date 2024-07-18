// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Projectile.h"
#include "Projectile_Fire.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AProjectile_Fire : public AS_Projectile
{
	GENERATED_BODY()
	
public:
	AProjectile_Fire();

	virtual void SetProjectile() override;

	virtual void Explode() override;
protected:
	class UParticleSystem* HitParticleEffect;

	class UParticleSystem* ParticleEffect;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UParticleSystemComponent* ProjectileParticle;
};
