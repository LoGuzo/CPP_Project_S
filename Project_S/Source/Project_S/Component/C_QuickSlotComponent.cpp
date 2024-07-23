// Fill out your copyright notice in the Description page of Project Settings.

#include "C_QuickSlotComponent.h"
#include "C_InventoryComponent.h"
#include "C_SkillComponent.h"

// Sets default values for this component's properties
UC_QuickSlotComponent::UC_QuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SkillSlots.SetNum(5);
	PotionSlots.SetNum(2);
}

void UC_QuickSlotComponent::UsePotionSlot(int32 _Index)
{
	PotionSlots[_Index].Amount--;
	if (PotionSlots[_Index].Amount < 1)
		PotionSlots[_Index] = FS_Slot();

	OnQuickUpdated.Broadcast();
}

void UC_QuickSlotComponent::SetSkillSlots(const TArray<FS_Slot>& _Slots)
{
	if (_Slots.Num() != 0)
		SkillSlots = _Slots;
}

void UC_QuickSlotComponent::SetPotionSlots(const TArray<FS_Slot>& _Slots)
{
	if (_Slots.Num() != 0)
		PotionSlots = _Slots;
}

void UC_QuickSlotComponent::SkillToQuick(int32 _SkillIndex, int32 _TargetIndex, UC_SkillComponent* _SkillCom)
{
	LocalSlot = _SkillCom->GetSlot(_SkillIndex);
	if (!SkillSlots.ContainsByPredicate([&](const FS_Slot& Slot) { return Slot.ItemName == LocalSlot.ItemName; }))
	{
		if (_TargetIndex >= 0)
			SkillSlots[_TargetIndex] = LocalSlot;
	}
	else {
		int32 Index = SkillSlots.IndexOfByPredicate([&](const FS_Slot& Slot) { return Slot.ItemName == LocalSlot.ItemName; });
		if (Index != INDEX_NONE)
		{
			if (_TargetIndex >= 0)
			{
				SkillSlots[Index] = SkillSlots[_TargetIndex];
				SkillSlots[_TargetIndex] = LocalSlot;
			}
		}
	}

	OnQuickUpdated.Broadcast();
}

void UC_QuickSlotComponent::InvenToQuick(int32 _InvenIndex, int32 _TargetIndex, UC_InventoryComponent* _InvenCom)
{
	LocalSlot = _InvenCom->GetSlot(_InvenIndex);
	int32 SumSize = 0;
	for (const FS_Slot& slot : _InvenCom->GetSlots())
	{
		if (slot.ItemName == LocalSlot.ItemName)
			SumSize += slot.Amount;
	}
	LocalSlot.Amount = SumSize;
	if (!PotionSlots.ContainsByPredicate([&](const FS_Slot& Slot) { return Slot.ItemName == LocalSlot.ItemName; }))
	{
		if (_TargetIndex >= 0)
			PotionSlots[_TargetIndex] = LocalSlot;
	}
	else {
		int32 Index = PotionSlots.IndexOfByPredicate([&](const FS_Slot& Slot) { return Slot.ItemName == LocalSlot.ItemName; });
		if (Index != INDEX_NONE)
		{
			if (_TargetIndex >= 0)
			{
				PotionSlots[Index] = PotionSlots[_TargetIndex];
				PotionSlots[_TargetIndex] = LocalSlot;
			}
		}
	}

	OnQuickUpdated.Broadcast();
}