// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Item.h"
#include "RedPotionActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ARedPotionActor : public AA_Item
{
	GENERATED_BODY()
	
public:
	ARedPotionActor();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* ItemMesh;

	virtual void SetW_Mesh(TSoftObjectPtr<UStreamableRenderAsset> _ItemMesh) override;
};
