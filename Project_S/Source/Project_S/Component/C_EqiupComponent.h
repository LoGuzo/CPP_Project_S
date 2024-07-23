// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_S/S_StructureAll.h"
#include "C_EqiupComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEquipUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API UC_EqiupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_EqiupComponent();

	FOnEquipUpdated OnEquipUpdated;
private:
	TArray<FS_Slot> Slots;

	FS_Slot LocalSlot;

protected:
	virtual void BeginPlay() override;

public:
	TArray<FS_Slot> GetSlots() { return Slots; }

	FS_Slot GetSlot(int32 _Index) { return Slots[_Index]; }
	
	void SetSlots(const TArray<FS_Slot>& _Slots);

	void SetSlot(int32 _Index, FS_Slot _Slot);
		
	void InvenToEquip(int32 _BeforeIndex, int32 _TargetIndex, class UC_InventoryComponent* _InvenCom);
	
	void ExchangeEquip(int32 _BeforeIndex, int32 _TargetIndex, TSubclassOf<class AA_Item> _ItemClass);
};
