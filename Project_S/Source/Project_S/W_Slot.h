// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Drag.h"
#include "DO_DragDrop.h"
#include "C_InventoryComponent.h"
#include "W_Slot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Slot : public UUserWidget
{
	GENERATED_BODY()

public:
	UW_Slot(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;

	FName GetIName() { return ItemKey; }
	int32 GetAmount() { return Amount; }
	int32 GetConIndex() { return ContentIndex; }

	void SetItemKey(FName _ItemKey);
	void SetAmount(int32 _Amount);
	void SetConIndex(int32 _ContentIndex);
	void SetInvenCom(UC_InventoryComponent* _InventoryCom);

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
private:

	TSubclassOf<class UW_Drag> U_DragImg;

	UW_Drag* DragImg;

	UDO_DragDrop* DO_Drag;

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

	int32 ContentIndex;

	UC_InventoryComponent* InventoryCom;
};
