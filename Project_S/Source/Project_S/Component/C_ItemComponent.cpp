// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ItemComponent.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "C_InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UC_ItemComponent::UC_ItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	ItemAmount = 1;
	// ...
}


// Called when the game starts
void UC_ItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UC_ItemComponent::Interact(AUserCharacter* _UserCharacter)
{
	if (_UserCharacter)
	{
		auto Inventory = _UserCharacter->GetInventoryCom();
		if (Inventory)
		{
			Inventory->AddItem(ItemAmount, RowName, Description.ToString(), ItemClass);
			GetOwner()->Destroy();
		}
	}
}

void UC_ItemComponent::SetItem(FString _ItemName)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (_ItemName != "") {
			auto ItemData = static_cast<FS_Item*>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetMyData(_ItemName));
			if (ItemData)
			{
				RowName = FName(*_ItemName);
				ItemName = ItemData->ItemName;
				Description = ItemData->Description;
				ItemImage = ItemData->ItemImage;
				StackSize = ItemData->StackSize;
				ItemType = ItemData->ItemType;
				ItemClass = ItemData->ItemClass;
			}
		}
	}
}
