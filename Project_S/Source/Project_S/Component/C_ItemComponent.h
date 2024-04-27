// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_S/Item/I_ItemInterface.h"
#include "Project_S/E_ItemType.h"
#include "C_ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API UC_ItemComponent : public UActorComponent, public II_ItemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_ItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
	TSubclassOf<class AA_Item> ItemClass;

public:	

	virtual void Interact(class AUserCharacter* _UserCharacter) override;
	void SetItem(FString _ItemName);
		
};
