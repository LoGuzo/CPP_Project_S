// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS(Abstract)
class PROJECT_S_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//AWeaponActor();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;
protected:
	UFUNCTION()
	virtual void SetW_Mesh() PURE_VIRTUAL(AWeaponActor::SetW_Mesh, ;);

	UFUNCTION()
	virtual void AttackCheck(class AUserCharacter* _UserCharacter) PURE_VIRTUAL(AWeaponActor::AttackCheck, ;);
};
