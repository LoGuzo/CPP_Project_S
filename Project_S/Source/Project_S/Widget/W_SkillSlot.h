// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UW_SkillSlot(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Skill;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Plus;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Minus;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Point;

	TSubclassOf<class UW_SkillImgSlot> TW_Slot;
	class UW_SkillImgSlot* W_Slot;

	class UC_SkillComponent* SkillCom;

	int32 SkillPoint;

	int32 MaxPoint=10;

	int32 SlotIndex;

	UFUNCTION()
	void SetTextPlus();
	UFUNCTION()
	void SetTextMinus();
public:
	int32 GetSkillPoint() { return SkillPoint; }
	void SetMaxPoint(const int32 _MaxPoint);
	void SetSkillCom(class UC_SkillComponent* _SkillCom);
	void UpdateImg(const FName _SkillName);
	void SetTextBlock(const int32 _SkillPoint);
	void SetSlotIndex(const int32 _SlotIndex);
};
