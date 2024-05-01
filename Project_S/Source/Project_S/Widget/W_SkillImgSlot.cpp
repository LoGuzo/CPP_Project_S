// Fill out your copyright notice in the Description page of Project Settings.


#include "W_SkillImgSlot.h"
#include "Components/Image.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Kismet/GameplayStatics.h"

UW_SkillImgSlot::UW_SkillImgSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_Drag>UW_Drag(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Drag.WBP_Drag_C'"));
	if (UW_Drag.Succeeded())
	{
		U_DragImg = UW_Drag.Class;
	}
}

void UW_SkillImgSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (SkillKey.ToString() != "None") {
			auto SkillData = static_cast<FSkillTable*>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Skill)->GetMyData(SkillKey.ToString()));
			if (SkillData)
			{
				Img_Skill->SetBrushFromTexture(SkillData->Skill_Img);
				Img_Skill->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UW_SkillImgSlot::SetSkillKey(FName _SkillKey)
{
	SkillKey = _SkillKey;
}
