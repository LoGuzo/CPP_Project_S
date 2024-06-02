// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ItemPop.h"
#include "Components/Button.h"
#include "Project_S/Component/C_InventoryComponent.h"

void UW_ItemPop::SetInvenCom(class UC_InventoryComponent* _InvenCom)
{
	InvenCom = _InvenCom;
}
void UW_ItemPop::SetTargetIndex(const int32 _TargetIndex)
{
	TargetIndex = _TargetIndex;
}
void UW_ItemPop::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Btn_ItemDrop)
	{
		Btn_ItemDrop->OnClicked.AddDynamic(this, &UW_ItemPop::ItemDrop);
	}
}

void UW_ItemPop::ItemDrop()
{
	if (InvenCom)
	{
		InvenCom->DropItem(TargetIndex);
		InvenCom->OnInventoryUpdated.Broadcast();
	}
	RemoveFromParent();
}