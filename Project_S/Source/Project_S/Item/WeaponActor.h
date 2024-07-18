// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Item.h"
#include "WeaponActor.generated.h"

UCLASS(Abstract)
class PROJECT_S_API AWeaponActor : public AA_Item
{
	GENERATED_BODY()
	
public:	
	//Sets default values for this actor's properties
	AWeaponActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	class UParticleSystem* ParticleEffect;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UParticleSystemComponent* WeaponParticle;
public:

	UFUNCTION()
	virtual void Fire() PURE_VIRTUAL(AWeaponActor::SetProjectile, ;);
};
