// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlyHpBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UOnlyHpBar : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void BindHp(class US_StatComponent* _StatComp);

	void UpdateHp();

private:
	TWeakObjectPtr<class US_StatComponent> StatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;
};
