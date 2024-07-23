// Fill out your copyright notice in the Description page of Project Settings.


#include "W_QuickSlot.h"
#include "DO_DragDrop.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Component/C_QuickSlotComponent.h"
#include "Project_S/Instance/S_GameInstance.h"

void UW_QuickSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		Txt_Quick->SetText(FText::FromString(FString::FromInt(SlotKey)));
		if (ItemKey.ToString() != "None") {
			ItemData = StaticCastSharedPtr<FS_Item>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetMyData(ItemKey.ToString()));
			if (ItemData.IsValid())
			{
				Img_Quick->SetBrushFromTexture(ItemData.Pin()->ItemImage);
				Box_Stack->SetVisibility(ESlateVisibility::Visible);
				Txt_Stack->SetText(FText::FromString(FString::FromInt(Amount)));
				Img_Quick->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else if (SkillKey.ToString() != "None") {
			SkillData = StaticCastSharedPtr<FSkillTable>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Skill)->GetMyData(SkillKey.ToString()));
			if (SkillData.IsValid())
			{
				Img_Quick->SetBrushFromTexture(SkillData.Pin()->Skill_Img);
				Img_Quick->SetVisibility(ESlateVisibility::Visible);
				Box_Stack->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			Box_Stack->SetVisibility(ESlateVisibility::Hidden);
			Img_Quick->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UW_QuickSlot::NativeDestruct()
{
	Super::NativeDestruct();

	if (ItemData != nullptr)
		ItemData.Reset();

	if (SkillData != nullptr)
		SkillData.Reset();
}

void UW_QuickSlot::SetConIndex(int32 _ContentIndex)
{
	ContentIndex = _ContentIndex;
}

void UW_QuickSlot::SetItemKey(FName _ItemKey)
{
	ItemKey = _ItemKey;
}

void UW_QuickSlot::SetSkillKey(FName _SkillKey)
{
	SkillKey = _SkillKey;
}

void UW_QuickSlot::SetConName(FString _ContentName)
{
	ContentName = _ContentName;
}

void UW_QuickSlot::SetSlotKey(int32 _SlotKey)
{
	SlotKey = _SlotKey;
}

void UW_QuickSlot::SetAmount(int32 _Amount)
{
	Amount = _Amount;
}

void UW_QuickSlot::SetQuickSlotCom(UC_QuickSlotComponent* _QuickSlotCom)
{
	QuickSlotCom = _QuickSlotCom;
}

bool UW_QuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DO_Drag = Cast<UDO_DragDrop>(InOperation);
	if (DO_Drag->GetConName() == GetConName())
	{
		if (DO_Drag->GetConName() == "Inventory")
		{
			if (DO_Drag->GetItemConName() == E_ItemType::E_Cunsumalbe)
			{
				if (DO_Drag->GetInvenCom() != nullptr)
					QuickSlotCom->InvenToQuick(DO_Drag->GetConIndex(), ContentIndex, DO_Drag->GetInvenCom());
			}
		}
		else if (DO_Drag->GetConName() == "Skill")
		{
			if (DO_Drag->GetSkillCom() != nullptr)
				QuickSlotCom->SkillToQuick(DO_Drag->GetConIndex(), ContentIndex, DO_Drag->GetSkillCom());
		}
	}

	return false;
}
