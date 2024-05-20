// Fill out your copyright notice in the Description page of Project Settings.


#include "DO_DragDrop.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include "Project_S/Component/C_EqiupComponent.h"

void UDO_DragDrop::SetItemConName(E_ItemType _ItemConName)
{
	ItemConName = _ItemConName;
}

void UDO_DragDrop::SetConName(FString _ContentName)
{
	ContentName = _ContentName;
}

void UDO_DragDrop::SetConIndex(int32 _ContentIndex)
{
	ContentIndex = _ContentIndex;
}

void UDO_DragDrop::SetInvenCom(UC_InventoryComponent* _InventoryCom)
{
	InventoryCom = _InventoryCom;
}

void UDO_DragDrop::SetEquipCom(UC_EqiupComponent* _EquipCom)
{
	EquipCom = _EquipCom;
}

void UDO_DragDrop::SetSkillCom(UC_SkillComponent* _SkillCom)
{
	SkillCom = _SkillCom;
}
