// Fill out your copyright notice in the Description page of Project Settings.


#include "W_SkillSlot.h"
#include "W_Slot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Project_S/Component/C_SkillComponent.h"

UW_SkillSlot::UW_SkillSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_Slot>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Slot.WBP_Slot_C'"));
	if (UW.Succeeded())
	{
		TW_Slot = UW.Class;
	}
}

void UW_SkillSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Plus->OnClicked.AddDynamic(this, &UW_SkillSlot::SetTextPlus);
	Btn_Minus->OnClicked.AddDynamic(this, &UW_SkillSlot::SetTextMinus);
}

void UW_SkillSlot::SetTextPlus()
{
	if (MaxPoint > SkillPoint) {
		SkillPoint++;
		SetTextBlock(SkillPoint);
		if (SkillCom)
		{
			SkillCom->SetSlot(SlotIndex, SkillPoint);
		}
	}
}

void UW_SkillSlot::SetTextMinus()
{
	if (SkillPoint > 0)
	{
		SkillPoint--;
		SetTextBlock(SkillPoint);
		if (SkillCom)
		{
			SkillCom->SetSlot(SlotIndex, SkillPoint);
		}
	}
}

void UW_SkillSlot::SetMaxPoint(const int32 _MaxPoint)
{
	MaxPoint = _MaxPoint;
}

void UW_SkillSlot::SetSkillCom(UC_SkillComponent* _SkillCom)
{
	SkillCom = _SkillCom;
}

void UW_SkillSlot::UpdateImg(const FName _SkillName)
{
	Wrap_Skill->ClearChildren();
	W_Slot = CreateWidget<UW_Slot>(GetWorld(), TW_Slot);
	if (W_Slot)
	{
		W_Slot->SetSkillKey(_SkillName);
		W_Slot->SetSkillCom(SkillCom);
	}
	Wrap_Skill->AddChild(W_Slot);
}

void UW_SkillSlot::SetTextBlock(const int32 _SkillPoint)
{
	SkillPoint = _SkillPoint;
	Txt_Point->SetText(FText::FromString(FString::FromInt(SkillPoint)));
}

void UW_SkillSlot::SetSlotIndex(const int32 _SlotIndex)
{
	SlotIndex = _SlotIndex;
}
