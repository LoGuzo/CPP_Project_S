// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_BossHp.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_BossHp : public UMainUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeDestruct() override;

	void BindHp(class US_StatComponent* _StatComp);

	void UpdateHp();

	void SetTxtName(const int32 Lvl, const FString& Name);

private:
	TWeakObjectPtr<class US_StatComponent> StatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Hp;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_LvName;

	UPROPERTY()
	FTimerHandle HealthUpdateTimerHandle;

	UPROPERTY()
	float HealthUpdateDuration;

	UPROPERTY()
	float HealthUpdateTime;

	UPROPERTY()
	float CurrentHealth;

	UPROPERTY()
	float TargetHealth;

	void AnimateHealthBar();
};
