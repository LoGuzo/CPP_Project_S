// Fill out your copyright notice in the Description page of Project Settings.


#include "DO_DragDrop.h"

void UDO_DragDrop::SetConName(FText _ContentName)
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
