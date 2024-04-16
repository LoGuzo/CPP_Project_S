// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API US_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class US_StatComponent* _StatComp);
	void BindMp(class US_StatComponent* _StatComp);
	void BindExp(class US_StatComponent* _StatComp);

	void UpdateHp();
	void UpdateMp();
	void UpdateExp();

private:
	TWeakObjectPtr<class US_StatComponent> SStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Exp;
};
