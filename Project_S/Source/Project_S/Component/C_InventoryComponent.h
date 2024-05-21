// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_S/S_StructureAll.h"
#include "C_InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

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
	FS_Slot LocalSlot;

	TWeakPtr<FS_Item> ItemData;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	FOnInventoryUpdated OnInventoryUpdated;

	TArray<FS_Slot> GetSlots() { return Slots; }

	FS_Slot GetSlot(int32 _Index) { return Slots[_Index]; }

	void SetSlots(const TArray<FS_Slot>& _Slots);

	void SetSlot(int32 _Index, FS_Slot _Slot);

	void UsePotionSlot(int32 _Index) { Slots[_Index].Amount -= 1; }

	void AddItem(int32 _Amount,FName _ItemKey, E_ItemType _ItemConName, TSubclassOf<class AA_Item> _ItemClass);

	FResult FindSlot(FName _ItemKey);

	int32 GetStackSize(FName _ItemKey);

	void IncreaseSlotStack(int32 _Index, int32 _Amount);

	FResult CheckSlotEmpty();

	void AddToNewSlot(FName _ItemKey, int32 _Amount, E_ItemType _ItemConName, TSubclassOf<class AA_Item> _ItemClass);

	void ChangeSlot(int32 _BeforeIndex, int32 _TargetIndex, UC_InventoryComponent* _BeforeInvenCom);

	void EquipToInven(int32 _BeforeIndex, int32 _TargetIndex, class UC_EqiupComponent* _EquipCom);

	void ExchangeEquip(int32 _BeforeIndex, int32 _TargetIndex, TSubclassOf<class AA_Item> _ItemClass);
};
