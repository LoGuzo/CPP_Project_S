// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Slot.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

UW_Slot::UW_Slot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_Drag>UW_Drag(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Drag.WBP_Drag_C'"));
	if (UW_Drag.Succeeded())
	{
		U_DragImg = UW_Drag.Class;
	}
}

void UW_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (ItemKey.ToString() != "None") {
			auto ItemData = static_cast<FS_Item*>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetData(ItemKey.ToString()));
			if (ItemData)
			{
				if (ItemData->ItemType == E_ItemType::E_Equip)
				{
					Img_Item->SetBrushFromTexture(ItemData->ItemImage);
					Box_Stack->SetVisibility(ESlateVisibility::Hidden);
					Img_Item->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					Img_Item->SetBrushFromTexture(ItemData->ItemImage);
					Box_Stack->SetVisibility(ESlateVisibility::Visible);
					Txt_Stack->SetText(FText::FromString(FString::FromInt(Amount)));
					Img_Item->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
		else
		{
			Box_Stack->SetVisibility(ESlateVisibility::Hidden);
			Img_Item->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UW_Slot::SetItemConName(FString _ItemConName)
{
	ItemConName = _ItemConName;
}

void UW_Slot::SetConName(FString _ContentName)
{
	ContentName = _ContentName;
}

void UW_Slot::SetItemKey(FName _ItemKey)
{
	ItemKey = _ItemKey;
}

void UW_Slot::SetAmount(int32 _Amount)
{
	Amount = _Amount;
}

void UW_Slot::SetConIndex(int32 _ContentIndex)
{
	ContentIndex = _ContentIndex;
}

void UW_Slot::SetInvenCom(UC_InventoryComponent* _InventoryCom)
{
	InventoryCom = _InventoryCom;
}

void UW_Slot::SetEquipCom(UC_EqiupComponent* _EquipCom)
{
	EquipCom = _EquipCom;
}


FReply UW_Slot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (ItemKey.ToString() != "None")
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			return reply.NativeReply;
		}
		else
		{
			return FReply::Unhandled();
		}
	}
	else
	{
		return FReply::Unhandled();
	}
}

bool UW_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DO_Drag = Cast<UDO_DragDrop>(InOperation);
	if (DO_Drag->GetConName() == "Inventory" )
	{
		if (DO_Drag->GetConName() == GetConName())
		{
			if (DO_Drag->GetConIndex() != ContentIndex || DO_Drag->GetInvenCom() != InventoryCom)
			{
				InventoryCom->ChangeSlot(DO_Drag->GetConIndex(), ContentIndex, InventoryCom);
			}
		}
		else
		{
			if (ItemKey.ToString() == "None" || DO_Drag->GetItemConName() == GetItemConName())
			{
				EquipCom->InvenToEquip(DO_Drag->GetConIndex(), ContentIndex, DO_Drag->GetInvenCom());
			}
		}
	}
	else
	{
		if (DO_Drag->GetConName() != GetConName())
		{
			if (GetConName() == "Inventory")
			{
				if (ItemKey.ToString() == "None" || DO_Drag->GetItemConName() == GetItemConName())
				{
					InventoryCom->EquipToInven(DO_Drag->GetConIndex(), ContentIndex, DO_Drag->GetEquipCom());
				}
			}
		}

	}
	return false;
}

void UW_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (OutOperation == nullptr)
	{
		if (U_DragImg)
		{
			DragImg = CreateWidget<UW_Drag>(GetWorld(), U_DragImg);
			if (DragImg)
			{
				DragImg->SetItemKey(ItemKey);
			}
		}
		DO_Drag = NewObject<UDO_DragDrop>();
		OutOperation = DO_Drag;
		if (DO_Drag)
		{
			DO_Drag->SetConIndex(ContentIndex);
			if (InventoryCom != nullptr)
			{
				DO_Drag->SetInvenCom(InventoryCom);
			}
			if (EquipCom != nullptr)
			{
				DO_Drag->SetEquipCom(EquipCom);
			}
			DO_Drag->SetConName(GetConName());
			DO_Drag->SetItemConName(GetItemConName());
			DO_Drag->DefaultDragVisual = DragImg;
		}
	}
}
