// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EqiupComponent.h"
#include "C_InventoryComponent.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Item/A_Item.h"

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
}

void UC_EqiupComponent::SetSlots(const TArray<FS_Slot>& _Slots)
{
	if (_Slots.Num() != 0)
		Slots = _Slots;
}

void UC_EqiupComponent::SetSlot(int32 _Index, FS_Slot _Slot)
{
	Slots[_Index] = _Slot;
}


void UC_EqiupComponent::InvenToEquip(int32 _BeforeIndex, int32 _TargetIndex, UC_InventoryComponent* _InvenCom)
{
	LocalSlot = _InvenCom->GetSlot(_BeforeIndex);
	if (_TargetIndex >= 0)
	{
		_InvenCom->SetSlot(_BeforeIndex, Slots[_TargetIndex]);
		Slots[_TargetIndex] = LocalSlot;
		ExchangeEquip(_BeforeIndex, _TargetIndex, _InvenCom->GetSlot(_BeforeIndex).ItemClass);
	}
	OnEquipUpdated.Broadcast();
	_InvenCom->OnInventoryUpdated.Broadcast();

}

void UC_EqiupComponent::ExchangeEquip(int32 _BeforeIndex, int32 _TargetIndex, TSubclassOf<class AA_Item> _ItemClass)
{
	auto userCharacter = Cast<AUserCharacter>(GetOwner());
	if (_TargetIndex == 0)
	{
		if (_ItemClass != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("ChangeWeapon"));
			userCharacter->RemoveMyWeapon();
		}
		userCharacter->SetMyWeapon(Slots[_TargetIndex].ItemClass);
	}
	else
	{

	}
}

