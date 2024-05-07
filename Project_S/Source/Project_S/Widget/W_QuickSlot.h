// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_QuickSlot.generated.h"

/**
 * 
 */
struct FS_Item;
struct FSkillTable;

UCLASS()
class PROJECT_S_API UW_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

	int32 GetSlotKey() { return SlotKey; }
	FName GetIName() { return ItemKey; }
	int32 GetAmount() { return Amount; }
	void SetItemKey(FName _ItemKey);
	void SetSlotKey(int32 _SlotKey);
	void SetAmount(int32 _Amount);

private:

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Quick;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* Box_Stack;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Stack;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Quick;

	UPROPERTY(VisibleAnywhere)
	FName ItemKey;

	UPROPERTY(VisibleAnywhere)
	int32 Amount;

	UPROPERTY(VisibleAnywhere)
	int32 SlotKey;

	UPROPERTY(VisibleAnywhere)
	FName SkillKey;

	TWeakPtr<FS_Item> ItemData;

	TWeakPtr<FSkillTable> SkillData;
};
