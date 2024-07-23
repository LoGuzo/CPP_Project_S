// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "StaffWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AStaffWeapon : public AWeaponActor
{
	GENERATED_BODY()
	
public:
	AStaffWeapon();

	virtual void SetW_Mesh(TSoftObjectPtr<UStreamableRenderAsset> _ItemMesh) override;

	virtual void Fire() override;
};
