// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EqiupComponent.h"

// Sets default values for this component's properties
UC_EqiupComponent::UC_EqiupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UC_EqiupComponent::BeginPlay()
{
	Super::BeginPlay();
	Slots.SetNum(5);
	Slots[0].ItemName = FName("BlackSword");
	Slots[0].Amount = 1;
}

void UC_EqiupComponent::SetSlot(int32 _Index, FS_Slot _Slot)
{
	Slots[_Index] = _Slot;
}

