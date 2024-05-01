// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_S/S_StructureAll.h"
#include "W_Skill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Skill : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UW_Skill(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Sp;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Vertical_Skill;

	class UC_SkillComponent* SkillCom;

	TSubclassOf<class UW_SkillSlot> TW_SkillSlot;

	class UW_SkillSlot* W_SkillSlot;

public:
	void SetTextSp(int32 _Sp);
	void ShowSkillWidget(class UC_SkillComponent* _SkillCom);
	void UpdateSlots(const TArray<FS_Slot>& _Slots);
};
