// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Skill.h"
#include "W_SkillSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Instance/S_GameInstance.h"

UW_Skill::UW_Skill(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_SkillSlot>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Skill_Slot.WBP_Skill_Slot_C'"));
	if (UW.Succeeded())
		TW_SkillSlot = UW.Class;
}

void UW_Skill::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(true);
	}
}

void UW_Skill::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameOnly InputMode;
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(false);
	}
}

void UW_Skill::NativePreConstruct()
{
	Super::NativePreConstruct();

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter)
	{
		SkillCom = playerCharacter->FindComponentByClass<UC_SkillComponent>();
		if (SkillCom)
			ShowSkillWidget(SkillCom);
	}
}



void UW_Skill::UpdateSlots(const TArray<FS_Slot>& _Slots)
{
	int32 index = 0;
	Vertical_Skill->ClearChildren();
	for (const FS_Slot& slot : _Slots)
	{
		W_SkillSlot = CreateWidget<UW_SkillSlot>(GetWorld(), TW_SkillSlot);
		if (W_SkillSlot) {
			W_SkillSlot->SetTextBlock(slot.Amount);
			W_SkillSlot->SetSkillCom(SkillCom);
			W_SkillSlot->UpdateImg(slot.ItemName);
			W_SkillSlot->SetSlotIndex(index);
		}
		Vertical_Skill->AddChild(W_SkillSlot);
		index++;
	}
}

void UW_Skill::ShowSkillWidget(UC_SkillComponent* _SkillCom)
{
	SkillCom = _SkillCom;
	UpdateSlots(SkillCom->GetSlots());
}

void UW_Skill::SetTextSp(int32 _Sp)
{
	Txt_Sp->SetText(FText::FromString(FString::Printf(TEXT("³²Àº : %d"), _Sp)));
}

