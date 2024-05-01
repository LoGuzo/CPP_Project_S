// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Drag.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"


void UW_Drag::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (!ItemKey.ToString().IsEmpty()) {
			auto ItemData = static_cast<FS_Item*>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetMyData(ItemKey.ToString()));
			if (ItemData)
			{
				Img_Drag->SetBrushFromTexture(ItemData->ItemImage);
			}
		}
	}
}

void UW_Drag::SetItemKey(FName _ItemKey)
{
	ItemKey = _ItemKey;
}
