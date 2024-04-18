// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_StructureAll.h"
#include "W_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Box_Wrap;

	class UC_InventoryComponent* InventoryCom;

	TSubclassOf<class UW_Slot> W_Slot;

public:
	virtual void NativeOnInitialized() override;

	void ShowInventory(UC_InventoryComponent* _InventoryCom);
	void UpdateSlots(const TArray<FS_Slot>& Slots);
};
