// Fill out your copyright notice in the Description page of Project Settings.


#include "C_InventoryComponent.h"
#include "S_GameInstance.h"
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

void UC_InventoryComponent::AddItem(int32 _Amount, FName _ItemKey)
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
				AddToNewSlot(_ItemKey, 1);
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
		if (!_ItemKey.ToString().IsEmpty()) {
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
	TArray<FS_Slot> Slots2;
	Slots2 = Slots;
	Slots[_Index].Amount=Slots2[_Index].Amount + _Amount;
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

void UC_InventoryComponent::AddToNewSlot(FName _ItemKey, int32 _Amount)
{
	FResult result;
	result = CheckSlotEmpty();
	Slots[result.Index].ItemName = _ItemKey;
	Slots[result.Index].Amount = _Amount;
}

