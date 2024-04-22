// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Slot.h"
#include "Components/WrapBox.h"
#include "W_Equip.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnEquipUpdated);
/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Equip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UW_Equip(const FObjectInitializer& ObjectInitializer);

	FOnEquipUpdated OnEquipUpdated;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativePreConstruct() override;

	void ShowEquip(class UC_EqiupComponent* _EquipCom);
	void UpdateEquip(const TArray<FS_Slot>& _Slots);
private:

	TSubclassOf<class UW_Slot> USlot_Weapon;
	TSubclassOf<class UW_Slot> USlot_Head;
	TSubclassOf<class UW_Slot> USlot_Shoes;
	TSubclassOf<class UW_Slot> USlot_Armor;
	TSubclassOf<class UW_Slot> USlot_Cape;

	UW_Slot* Slot_Weapon;
	UW_Slot* Slot_Head;
	UW_Slot* Slot_Shoes;
	UW_Slot* Slot_Armor;
	UW_Slot* Slot_Cape;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* Wrap_Weapon;
	UPROPERTY(meta = (BindWidget))
	UWrapBox* Wrap_Head;
	UPROPERTY(meta = (BindWidget))
	UWrapBox* Wrap_Shoes;
	UPROPERTY(meta = (BindWidget))
	UWrapBox* Wrap_Armor;
	UPROPERTY(meta = (BindWidget))
	UWrapBox* Wrap_Cape;

	class UC_EqiupComponent* equipCom;

	TMap<int32, FText> EquipMap = { 
	{0, FText::FromString(TEXT("Weapon"))},
	{1, FText::FromString(TEXT("Head"))} ,
	{2, FText::FromString(TEXT("Armor"))} ,
	{3, FText::FromString(TEXT("Shoes"))} ,
	{4, FText::FromString(TEXT("Cape"))} 
	};
};
