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

class UDO_DragDrop;
class UC_QuickSlotComponent;

UCLASS()
class PROJECT_S_API UW_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

	int32 GetSlotKey() { return SlotKey; }
	FName GetIName() { return ItemKey; }
	int32 GetContentIndex() { return ContentIndex; }
	int32 GetAmount() { return Amount; }
	UC_QuickSlotComponent* GetQuickSlotCom() { return QuickSlotCom; }

	void SetItemKey(FName _ItemKey);
	void SetSlotKey(int32 _SlotKey);
	void SetConIndex(int32 _ContentIndex);
	void SetAmount(int32 _Amount);
	void SetQuickSlotCom(UC_QuickSlotComponent* _QuickSlotCom);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:

	UDO_DragDrop* DO_Drag;

	UC_QuickSlotComponent* QuickSlotCom;

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
	
	UPROPERTY(VisibleAnywhere)
	int32 ContentIndex;

	TWeakPtr<FS_Item> ItemData;

	TWeakPtr<FSkillTable> SkillData;
};
