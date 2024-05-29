// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DO_DragDrop.h"
#include "Project_S/E_ItemType.h"
#include "W_Slot.generated.h"

/**
 * 
 */
struct FS_Item;
struct FSkillTable;
class UW_Drag;
class UC_InventoryComponent;
class UC_EqiupComponent;
class UC_SkillComponent;

UCLASS()
class PROJECT_S_API UW_Slot : public UUserWidget
{
	GENERATED_BODY()

public:
	UW_Slot(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

	FName GetIName() { return ItemKey; }
	E_ItemType GetItemConName() { return ItemConName; }
	FString GetConName() { return ContentName; }
	int32 GetAmount() { return Amount; }
	int32 GetConIndex() { return ContentIndex; }
	FName GetSkillKey() { return SkillKey; }

	void SetSkillKey(FName _SkillKey);
	void SetItemConName(E_ItemType _ItemConName);
	void SetConName(FString _ContentName);
	void SetItemKey(FName _ItemKey);
	void SetAmount(int32 _Amount);
	void SetConIndex(int32 _ContentIndex);
	void SetInvenCom(UC_InventoryComponent* _InventoryCom);
	void SetEquipCom(UC_EqiupComponent* _EquipCom);
	void SetSkillCom(UC_SkillComponent* _SkillCom);

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
private:

	TSubclassOf<UW_Drag> U_DragImg;

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

	UPROPERTY(VisibleAnywhere)
	FName SkillKey;

	UPROPERTY(VisibleAnywhere)
	FString ContentName;

	UPROPERTY(VisibleAnywhere)
	E_ItemType ItemConName;

	UPROPERTY(VisibleAnywhere)
	int32 ContentIndex;

	UC_InventoryComponent* InventoryCom;

	UC_EqiupComponent* EquipCom;

	UC_SkillComponent* SkillCom;

	TWeakPtr<FS_Item> ItemData;

	TWeakPtr<FSkillTable> SkillData;
};
