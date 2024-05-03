// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SkillComponent.h"

// Sets default values for this component's properties
UC_SkillComponent::UC_SkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UC_SkillComponent::BeginPlay()
{
	Super::BeginPlay();
	Slots.SetNum(SkillCnt);

	Slots[0].ItemName = FName("SpinAttack");
	Slots[0].Amount = 1;
}

void UC_SkillComponent::SetSlots(const TArray<FS_Slot>& _Slots)
{
	Slots = _Slots;
}

void UC_SkillComponent::SetSlot(int32 _Index, int32 _SkillPoint)
{
	Slots[_Index].Amount = _SkillPoint;
}
