// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Inventory.h"
#include "Components/WrapBox.h"
#include "W_Slot.h"
#include "C_InventoryComponent.h"


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
}

void UW_Inventory::UpdateSlots(const TArray<FS_Slot>& _Slots)
{
	for (const FS_Slot& slot : _Slots)
	{
		W_Slots = CreateWidget<UW_Slot>(GetWorld(), W_Slot);
		if (W_Slots)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Open"));
			W_Slots->SetItemKey(slot.ItemName);
			W_Slots->SetAmount(slot.Amount);
		}
		Box_Wrap->AddChild(W_Slots);
	}
}
