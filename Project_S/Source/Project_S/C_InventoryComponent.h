// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_StructureAll.h"
#include "C_InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API UC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_InventoryComponent();

private:
	int32 InventorySize;
	TArray<FS_Slot> Slots;
	bool IsAddFailed;

	int32 AmountLeft;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	TArray<FS_Slot> GetSlots() { return Slots; }

	void AddItem(int32 _Amount,FName _ItemKey);

	FResult FindSlot(FName _ItemKey);

	int32 GetStackSize(FName _ItemKey);

	void IncreaseSlotStack(int32 _Index, int32 _Amount);

	FResult CheckSlotEmpty();

	void AddToNewSlot(FName _ItemKey, int32 _Amount);
};
