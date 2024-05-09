// Fill out your copyright notice in the Description page of Project Settings.


#include "W_QuickSlotMenu.h"
#include "W_QuickSlot.h"
#include "Components/WrapBox.h"
#include "Project_S/Component/C_QuickSlotComponent.h"


UW_QuickSlotMenu::UW_QuickSlotMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_QuickSlot>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_QuickSlot.WBP_QuickSlot_C'"));
	if (UW.Succeeded())
	{
		W_Slot = UW.Class;
	}
}

void UW_QuickSlotMenu::UpdateSkillSlots(const TArray<FS_Slot>& _Slots)
{
	int32 index = 0;
	Wrap_Quick->ClearChildren();
	for (const FS_Slot& slot : _Slots)
	{
		W_Slots2 = CreateWidget<UW_QuickSlot>(GetWorld(), W_Slot);
		if (W_Slots2)
		{
			W_Slots2->SetSkillKey(slot.ItemName);
			W_Slots2->SetAmount(slot.Amount);
			W_Slots2->SetQuickSlotCom(QuickSlotCom);
			W_Slots2->SetConName("Skill");
			W_Slots2->SetConIndex(index);
			W_Slots2->SetSlotKey(index + 1);

		}
		Wrap_Quick->AddChild(W_Slots2);
		index++;
	}
}

void UW_QuickSlotMenu::UpdatePotionSlots(const TArray<FS_Slot>& _Slots)
{
	int32 index = 0;
	Wrap_Quick->ClearChildren();
	for (const FS_Slot& slot : _Slots)
	{
		W_Slots2 = CreateWidget<UW_QuickSlot>(GetWorld(), W_Slot);
		if (W_Slots2)
		{
			W_Slots2->SetItemKey(slot.ItemName);
			W_Slots2->SetAmount(slot.Amount);
			W_Slots2->SetQuickSlotCom(QuickSlotCom);
			W_Slots2->SetConName("Inventory");
			W_Slots2->SetConIndex(index);
			W_Slots2->SetSlotKey(index + 6);

		}
		Wrap_Quick->AddChild(W_Slots2);
		index++;
	}
}

void UW_QuickSlotMenu::ShowQSkillWidget(UC_QuickSlotComponent* _QuickSlotCom)
{
	QuickSlotCom = _QuickSlotCom;
	UpdateSkillSlots(_QuickSlotCom->GetSkillSlots());
}

void UW_QuickSlotMenu::ShowQPotionWidget(UC_QuickSlotComponent* _QuickSlotCom)
{
	QuickSlotCom = _QuickSlotCom;
	UpdatePotionSlots(_QuickSlotCom->GetPotionSlots());
}

