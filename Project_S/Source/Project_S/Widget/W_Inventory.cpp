// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Inventory.h"
#include "W_Slot.h"
#include "Components/WrapBox.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/C_InventoryComponent.h"


UW_Inventory::UW_Inventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_Slot>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Slot.WBP_Slot_C'"));
	if (UW.Succeeded())
	{
		W_Slot = UW.Class;
	}
}

void UW_Inventory::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (InventoryCom)
	{
		UpdateSlots(InventoryCom->GetSlots());
	}
}

void UW_Inventory::ShowInventory(UC_InventoryComponent* _InventoryCom)
{
	InventoryCom = _InventoryCom;
	Box_Wrap->ClearChildren();
	UpdateSlots(InventoryCom->GetSlots());
	InventoryCom->OnInventoryUpdated.AddUObject(this, &UW_Inventory::ShowInventoryDrop);
}

void UW_Inventory::ShowInventoryDrop()
{
	Box_Wrap->ClearChildren();
	UpdateSlots(InventoryCom->GetSlots());
}

void UW_Inventory::UpdateSlots(const TArray<FS_Slot>& _Slots)
{
	int32 index = 0;
	for (const FS_Slot& slot : _Slots)
	{
		W_Slots2 = CreateWidget<UW_Slot>(GetWorld(), W_Slot);
		if (W_Slots2)
		{
			W_Slots2->SetItemKey(slot.ItemName);
			W_Slots2->SetAmount(slot.Amount);
			W_Slots2->SetItemConName(slot.ItemConName);
			W_Slots2->SetInvenCom(InventoryCom);
			W_Slots2->SetConName("Inventory");
			W_Slots2->SetConIndex(index);
			W_Slots2->OnCloseItemPop.AddUObject(this, &UW_Inventory::ClosePop);
		}
		Box_Wrap->AddChild(W_Slots2);
		index++;
	}
}

void UW_Inventory::ClosePop()
{
	if (Box_Wrap)
	{
		for (UWidget* Widget : Box_Wrap->GetAllChildren())
		{
			UW_Slot* SlotWidget = Cast<UW_Slot>(Widget);
			if (SlotWidget)
				if (SlotWidget->ClosePop())
					return;
		}
	}
}
