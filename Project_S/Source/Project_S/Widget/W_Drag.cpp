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
		if (ItemKey.ToString() != "None")
		{
			ItemData = StaticCastSharedPtr<FS_Item>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetMyData(ItemKey.ToString()));
			if (ItemData.IsValid())
				Img_Drag->SetBrushFromTexture(ItemData.Pin()->ItemImage);
		}
		else if (SkillKey.ToString() != "None")
		{
			SkillData = StaticCastSharedPtr<FSkillTable>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Skill)->GetMyData(SkillKey.ToString()));
			if (SkillData.IsValid())
			{
				if (SkillData.IsValid())
					Img_Drag->SetBrushFromTexture(SkillData.Pin()->Skill_Img);
			}
		}
	}
}

void UW_Drag::SetItemKey(FName _ItemKey)
{
	ItemKey = _ItemKey;
}

void UW_Drag::SetSkillKey(FName _SkillKey)
{
	SkillKey = _SkillKey;
}
