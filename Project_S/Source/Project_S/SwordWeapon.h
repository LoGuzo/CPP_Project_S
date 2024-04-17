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
	virtual void SetW_Mesh() override;
	virtual void AttackCheck(class AUserCharacter* _UserCharacter) override;
};
