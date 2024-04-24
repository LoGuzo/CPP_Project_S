// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "C_InventoryComponent.h"
#include "C_EqiupComponent.h"
#include "DO_DragDrop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UDO_DragDrop : public UDragDropOperation
{
	GENERATED_BODY()
	
private:
	FString ContentName;
	FString ItemConName;
	int32 ContentIndex;
	UC_InventoryComponent* InventoryCom;
	UC_EqiupComponent* EquipCom;

public:
	FString GetConName() { return ContentName; }
	FString GetItemConName() { return ItemConName; }
	int32 GetConIndex() { return ContentIndex; }
	UC_InventoryComponent* GetInvenCom(){ return InventoryCom; }
	UC_EqiupComponent* GetEquipCom() { return EquipCom; }
	void SetItemConName(FString _ItemConName);
	void SetConName(FString _ContentName);
	void SetConIndex(int32 _ContentIndex);
	void SetInvenCom(UC_InventoryComponent* _InventoryCom);
	void SetEquipCom(UC_EqiupComponent* _EquipCom);
};
