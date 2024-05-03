// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "SwordWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ASwordWeapon : public AWeaponActor
{
	GENERATED_BODY()
	
public:
	ASwordWeapon();
	virtual void BeginPlay() override;

	virtual void SetW_Mesh() override;

	class UParticleSystem* GetParticle() { return HitParticleEffect; }
	virtual void AttackCheck(class AUserCharacter* _UserCharacter) override;
private:
	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* HitParticleEffect;
};
