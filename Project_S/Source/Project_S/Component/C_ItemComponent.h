// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_S/Item/I_ItemInterface.h"
#include "Project_S/E_ItemType.h"
#include "C_ItemComponent.generated.h"

struct FS_Item;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API UC_ItemComponent : public UActorComponent, public II_ItemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_ItemComponent();
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	FName RowName;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	FText ItemName;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	FText Description;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	int32 StackSize;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	E_ItemType ItemType;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	int32 ItemAmount;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	float DropChance;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class AA_Item> ItemClass;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UStreamableRenderAsset> ItemMesh;

	TWeakPtr<FS_Item> ItemData;

public:	
	virtual void Interact(class AUserCharacter* _UserCharacter) override;
	void SetItem(const FString& _ItemName);
	FString GetItemName() { return ItemName.ToString(); }

	TSoftObjectPtr<UStreamableRenderAsset> GetItemMesh() { return ItemMesh; }
	E_ItemType GetType() { return ItemType; }
		
};
