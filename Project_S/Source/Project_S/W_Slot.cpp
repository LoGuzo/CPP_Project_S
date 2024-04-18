// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Slot.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UW_Slot::NativePreConstruct()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (!ItemKey.ToString().IsEmpty()) {
			auto ItemData = MyGameInstance->GetItemData(ItemKey.ToString());
			if (ItemData)
			{
				Img_Item->SetBrushFromTexture(ItemData->ItemImage);
				Box_Stack->SetVisibility(ESlateVisibility::Visible);
				Txt_Stack->SetText(FText::FromString(FString::FromInt(Amount)));
				Img_Item->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				Box_Stack->SetVisibility(ESlateVisibility::Hidden);
				Img_Item->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UW_Slot::SetItemKey(FName _ItemKey)
{
	ItemKey = _ItemKey;
}

void UW_Slot::SetAmount(int32 _Amount)
{
	Amount = _Amount;
}
