// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_CharInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_CharInfo : public UMainUserWidget
{
	GENERATED_BODY()
public:
	void BindHp(class US_StatComponent* _StatComp);
	void BindMp(class US_StatComponent* _StatComp);
	void BindExp(class US_StatComponent* _StatComp);
	void BindLvl(class US_StatComponent* _StatComp);

	void UpdateHp();
	void UpdateMp();
	void UpdateExp();
	void UpdateLvl();

private:
	TWeakObjectPtr<class US_StatComponent> SStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Box_Info;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Exp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Lvl;
};
