// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_S/S_StructureAll.h"
#include "W_QuickSlotMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_QuickSlotMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UW_QuickSlotMenu(const FObjectInitializer& ObjectInitializer);
	void UpdateSkillSlots(const TArray<FS_Slot>& _Slots);
	void UpdatePotionSlots(const TArray<FS_Slot>& _Slots);

private:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Quick;

	TSubclassOf<class UW_QuickSlot> W_Slot;
	class UW_QuickSlot* W_Slots2;

};
