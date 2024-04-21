// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Drag.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"


void UW_Drag::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (!ItemKey.ToString().IsEmpty()) {
			auto ItemData = MyGameInstance->GetItemData(ItemKey.ToString());
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
