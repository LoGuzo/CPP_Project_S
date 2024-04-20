// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.h"
#include "S_CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API US_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	US_CharacterWidget(const FObjectInitializer& ObjectInitializer);

	void BindHp(class US_StatComponent* _StatComp);
	void BindMp(class US_StatComponent* _StatComp);
	void BindExp(class US_StatComponent* _StatComp);

	void UpdateHp();
	void UpdateMp();
	void UpdateExp();

	void ShowInventory();
	void RemoveInventory();

	void ShowEquip();
	void RemoveEquip();

	UInventoryMenu* GetInvetoryWidget() { return InventoryWidget; }

private:
	TWeakObjectPtr<class US_StatComponent> SStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Exp;

	TSubclassOf<class UInventoryMenu> U_InventoryWidget;

	UInventoryMenu* InventoryWidget;

	TSubclassOf<class UUserWidget> U_EquipmentWidget;

	UUserWidget* EquipmentWidget;

};
