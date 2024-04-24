// Fill out your copyright notice in the Description page of Project Settings.


#include "C_InventoryComponent.h"
#include "S_GameInstance.h"
#include "UserCharacter.h"
#include "C_EqiupComponent.h"
#include "A_Item.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UC_InventoryComponent::UC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	InventorySize = 16;
}


// Called when the game starts
void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Slots.SetNum(InventorySize);
	
}

void UC_InventoryComponent::SetSlot(int32 _Index, FS_Slot _Slot)
{
	Slots[_Index] = _Slot;
}

void UC_InventoryComponent::AddItem(int32 _Amount, FName _ItemKey, FString _ItemConName, TSubclassOf<class AA_Item> _ItemClass)
{
	AmountLeft = _Amount;
	FResult result;
	while (AmountLeft > 0 && !IsAddFailed)
	{
		result =  FindSlot(_ItemKey);
		if (result.IsFindItem) {
			IncreaseSlotStack(result.Index, 1);
			AmountLeft--;
		}
		else
		{
			result = CheckSlotEmpty();
			if (result.IsFindItem)
			{
				AddToNewSlot(_ItemKey, 1, _ItemConName, _ItemClass);
				AmountLeft--;
			}
			else 
			{
				IsAddFailed = true;
			}
		}
	}
}

FResult UC_InventoryComponent::FindSlot(FName _ItemKey)
{
	int32 index = 0;
	FResult result;
	for (const FS_Slot& Slot : Slots) {
		if (Slot.ItemName == _ItemKey)
		{
			if (Slot.Amount < GetStackSize(_ItemKey))
			{
				result.Index = index;
				result.IsFindItem = true;
				return result;
			}
		}
		index++;
	}
	result.Index = -1;
	result.IsFindItem = false;
	return result;

}

int32 UC_InventoryComponent::GetStackSize(FName _ItemKey)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (_ItemKey.ToString() != "None") {
			auto ItemData = MyGameInstance->GetItemData(_ItemKey.ToString());
			if (ItemData)
			{
				return ItemData->StackSize;
			}
		}
	}
	return -1;
}

void UC_InventoryComponent::IncreaseSlotStack(int32 _Index, int32 _Amount)
{
	Slots[_Index].Amount = Slots[_Index].Amount + _Amount;
}

FResult UC_InventoryComponent::CheckSlotEmpty()
{
	int32 index = 0;
	FResult result;
	for (const FS_Slot& Slot : Slots) {
		if (Slot.Amount == 0)
		{
			result.Index = index;
			result.IsFindItem = true;
			return result;
		}
		index++;
	}
	result.Index = -1;
	result.IsFindItem = false;
	return result;
}

void UC_InventoryComponent::AddToNewSlot(FName _ItemKey, int32 _Amount, FString _ItemConName, TSubclassOf<class AA_Item> _ItemClass)
{
	FResult result;
	result = CheckSlotEmpty();
	Slots[result.Index].ItemName = _ItemKey;
	Slots[result.Index].Amount = _Amount;
	Slots[result.Index].ItemConName = _ItemConName;
	Slots[result.Index].ItemClass = _ItemClass;
}

void UC_InventoryComponent::ChangeSlot(int32 _BeforeIndex, int32 _TargetIndex, UC_InventoryComponent* _BeforeInvenCom)
{
	LocalSlot = _BeforeInvenCom->GetSlot(_BeforeIndex);
	if (_TargetIndex >= 0)
	{
		if (LocalSlot.ItemName != Slots[_TargetIndex].ItemName)
		{
			_BeforeInvenCom->SetSlot(_BeforeIndex,  Slots[_TargetIndex]);
			Slots[_TargetIndex] = LocalSlot;
		
		}
		else {
			_BeforeInvenCom->SetSlot(_BeforeIndex, Slots[_TargetIndex]);
			Slots[_TargetIndex] = LocalSlot;
		}
	}
	OnInventoryUpdated.Broadcast();
}

void UC_InventoryComponent::EquipToInven(int32 _BeforeIndex, int32 _TargetIndex, class UC_EqiupComponent* _EquipCom)
{
	LocalSlot = _EquipCom->GetSlot(_BeforeIndex);
	if (_TargetIndex >= 0)
	{
		_EquipCom->SetSlot(_BeforeIndex, Slots[_TargetIndex]);
		Slots[_TargetIndex] = LocalSlot;
		ExchangeEquip(_BeforeIndex, _TargetIndex, _EquipCom->GetSlot(_BeforeIndex).ItemClass);
	}

	OnInventoryUpdated.Broadcast();
	_EquipCom->OnEquipUpdated.Broadcast();
}

void UC_InventoryComponent::ExchangeEquip(int32 _BeforeIndex, int32 _TargetIndex, TSubclassOf<class AA_Item> _ItemClass)
{
	auto userCharacter = Cast<AUserCharacter>(GetOwner());
	if (_BeforeIndex == 0)
	{
		userCharacter->RemoveMyWeapon();
		if (_ItemClass != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("ChangeWeapon"));
			TSubclassOf<class AWeaponActor> Weapon = Slots[_TargetIndex].ItemClass;
			userCharacter->SetMyWeapon(Weapon);
		}
	}
}
