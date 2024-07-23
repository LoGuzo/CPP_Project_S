// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Project_S/E_ItemType.h"
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

	E_ItemType ItemConName;

	int32 ContentIndex;

	UC_InventoryComponent* InventoryCom;

	UC_EqiupComponent* EquipCom;

	UC_SkillComponent* SkillCom;

public:
	FString GetConName() { return ContentName; }
	void SetConName(FString _ContentName);

	E_ItemType GetItemConName() { return ItemConName; }
	void SetItemConName(E_ItemType _ItemConName);

	int32 GetConIndex() { return ContentIndex; }
	void SetConIndex(int32 _ContentIndex);

	UC_InventoryComponent* GetInvenCom(){ return InventoryCom; }
	void SetInvenCom(UC_InventoryComponent* _InventoryCom);

	UC_EqiupComponent* GetEquipCom() { return EquipCom; }
	void SetEquipCom(UC_EqiupComponent* _EquipCom);

	UC_SkillComponent* GetSkillCom() { return SkillCom; }
	void SetSkillCom(UC_SkillComponent* _SkillCom);
};
