// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "C_InventoryComponent.h"
#include "DO_DragDrop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UDO_DragDrop : public UDragDropOperation
{
	GENERATED_BODY()
	
private:
	int32 ContentIndex;
	UC_InventoryComponent* InventoryCom;

public:
	int32 GetConIndex() { return ContentIndex; }
	UC_InventoryComponent* GetInvenCom(){ return InventoryCom; }
	void SetConIndex(int32 _ContentIndex);
	void SetInvenCom(UC_InventoryComponent* _InventoryCom);
};
