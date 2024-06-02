// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Slot.h"
#include "W_Drag.h"
#include "W_ItemPop.h"
#include "DO_DragDrop.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include "Project_S/Component/C_EqiupComponent.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Instance/S_GameInstance.h"


UW_Slot::UW_Slot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_Drag>BP_Drag(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Drag.WBP_Drag_C'"));
	if (BP_Drag.Succeeded())
	{
		U_DragImg = BP_Drag.Class;
	}
	static ConstructorHelpers::FClassFinder<UW_ItemPop>BP_ItemPop(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_ItemPop.WBP_ItemPop_C'"));
	if (BP_ItemPop.Succeeded())
	{
		U_ItemPop = BP_ItemPop.Class;
	}
}

void UW_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (ItemKey.ToString() != "None") {
			ItemData = StaticCastSharedPtr<FS_Item>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetMyData(ItemKey.ToString()));
			if (ItemData.IsValid())
			{
				if (ItemData.Pin()->ItemType == E_ItemType::E_Equip)
				{
					Img_Item->SetBrushFromTexture(ItemData.Pin()->ItemImage);
					Box_Stack->SetVisibility(ESlateVisibility::Hidden);
					Img_Item->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					Img_Item->SetBrushFromTexture(ItemData.Pin()->ItemImage);
					Box_Stack->SetVisibility(ESlateVisibility::Visible);
					Txt_Stack->SetText(FText::FromString(FString::FromInt(Amount)));
					Img_Item->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
		else if (SkillKey.ToString() != "None") {
			SkillData = StaticCastSharedPtr<FSkillTable>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Skill)->GetMyData(SkillKey.ToString()));
			if (SkillData.IsValid())
			{
				Img_Item->SetBrushFromTexture(SkillData.Pin()->Skill_Img);
				Img_Item->SetVisibility(ESlateVisibility::Visible);
				Box_Stack->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			Box_Stack->SetVisibility(ESlateVisibility::Hidden);
			Img_Item->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UW_Slot::NativeDestruct()
{
	Super::NativeDestruct();
	if (ItemData != nullptr)
	{
		ItemData.Reset();
	}
	if (SkillData != nullptr)
	{
		SkillData.Reset();
	}
	ClosePop();
}

void UW_Slot::SetItemConName(E_ItemType _ItemConName)
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

void UW_Slot::SetSkillCom(UC_SkillComponent* _SkillCom)
{
	SkillCom = _SkillCom;
}


FReply UW_Slot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (ItemKey.ToString() != "None" || SkillKey.ToString() != "None")
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			return reply.NativeReply;
		}
		else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			if (U_ItemPop)
			{
				OnCloseItemPop.Broadcast();
				ItemPop = CreateWidget<UW_ItemPop>(GetWorld(), U_ItemPop);
				if (ItemPop)
				{
					if (InventoryCom)
					{
						ItemPop->SetInvenCom(InventoryCom);
						ItemPop->SetTargetIndex(ContentIndex);
						ItemPop->AddToViewport();

						FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();
						FVector2D ViewportPosition = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this).AbsoluteToLocal(MousePosition);
						ItemPop->SetPositionInViewport(ViewportPosition, false);
					}
				}
			}
			return FReply::Handled();
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
			if (ItemKey.ToString() == "None" && DO_Drag->GetItemConName() == GetItemConName())
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
				if (ItemKey.ToString() != "None")
				{
					DragImg->SetItemKey(ItemKey);
				}
				else if (SkillKey.ToString() != "None")
				{
					DragImg->SetSkillKey(SkillKey);
				}
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
			if (SkillCom != nullptr)
			{
				DO_Drag->SetSkillCom(SkillCom);
			}
			DO_Drag->SetConName(GetConName());
			DO_Drag->SetItemConName(GetItemConName());
			DO_Drag->DefaultDragVisual = DragImg;
		}
	}
}

void UW_Slot::SetSkillKey(FName _SkillKey)
{
	SkillKey = _SkillKey;
}

bool UW_Slot::ClosePop()
{
	if (ItemPop)
	{
		ItemPop->RemoveFromParent();
		ItemPop = nullptr;
		return true;
	}
	return false;
}