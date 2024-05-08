// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DO_DragDrop.generated.h"

/**
 * 
 */
class UC_InventoryComponent;
class UC_EqiupComponent;
class UC_SkillComponent;

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
	UC_SkillComponent* SkillCom;

public:
	FString GetConName() { return ContentName; }
	FString GetItemConName() { return ItemConName; }
	int32 GetConIndex() { return ContentIndex; }
	UC_InventoryComponent* GetInvenCom(){ return InventoryCom; }
	UC_EqiupComponent* GetEquipCom() { return EquipCom; }
	UC_SkillComponent* GetSkillCom() { return SkillCom; }
	void SetItemConName(FString _ItemConName);
	void SetConName(FString _ContentName);
	void SetConIndex(int32 _ContentIndex);
	void SetInvenCom(UC_InventoryComponent* _InventoryCom);
	void SetEquipCom(UC_EqiupComponent* _EquipCom);
	void SetSkillCom(UC_SkillComponent* _SkillCom);
};
