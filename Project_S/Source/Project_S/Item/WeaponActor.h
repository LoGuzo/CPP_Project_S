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
	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	/*UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AS_Projectile> ProjectileClass;*/

protected:

private:

public:
	UFUNCTION()
	virtual void AttackCheck(class AUserCharacter* _UserCharacter) PURE_VIRTUAL(AWeaponActor::AttackCheck, ;);
};
