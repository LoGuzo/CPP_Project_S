// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_PartyHp.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_PartyHp : public UMainUserWidget
{
	GENERATED_BODY()
	
public:
	UW_PartyHp(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Slot;

	TSubclassOf<class UUserWidget> TW_PartyHpSlot;
	class UW_PartyHpSlot* W_PartyHpSlot;
};
