// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Slot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Slot : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativePreConstruct() override;

	FName GetIName() { return ItemKey; }
	int32 GetAmount() { return Amount; }

	void SetItemKey(FName _ItemKey);
	void SetAmount(int32 _Amount);
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* Box_Stack;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Stack;

	UPROPERTY(VisibleAnywhere)
	FName ItemKey;
	
	UPROPERTY(VisibleAnywhere)
	int32 Amount;
};
