// Fill out your copyright notice in the Description page of Project Settings.

#include "C_InventoryComponent.h"
#include "C_QuickSlotComponent.h"
#include "C_SkillComponent.h"

// Sets default values for this component's properties
UC_QuickSlotComponent::UC_QuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UC_QuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SkillSlots.SetNum(5);
	PotionSlots.SetNum(2);
}

void UC_QuickSlotComponent::SkillToQuick(int32 _SkillIndex, int32 _TargetIndex, UC_SkillComponent* _SkillCom)
{
	LocalSlot = _SkillCom->GetSlot(_SkillIndex);
	if (_TargetIndex >= 0)
	{
		SkillSlots[_TargetIndex] = LocalSlot;
	}

}

void UC_QuickSlotComponent::InvenToQuick(int32 _InvenIndex, int32 _TargetIndex, UC_InventoryComponent* _InvenCom)
{
	LocalSlot = _InvenCom->GetSlot(_InvenIndex);
	if (_TargetIndex >= 0)
	{
		PotionSlots[_TargetIndex] = LocalSlot;
	}

}