// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CharacterWidget.generated.h"

/**
 * 
 */

class UInventoryMenu;
class UW_Equip;
class UW_Skill;
class UW_QuickSlotMenu;

UCLASS()
class PROJECT_S_API US_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	US_CharacterWidget(const FObjectInitializer& ObjectInitializer);

	void BindHp(class US_StatComponent* _StatComp);
	void BindMp(class US_StatComponent* _StatComp);
	void BindExp(class US_StatComponent* _StatComp);
	void BindLvl(class US_StatComponent* _StatComp);

	void UpdateHp();
	void UpdateMp();
	void UpdateExp();
	void UpdateLvl();

	void ShowInventory();
	void RemoveInventory() const;

	void ShowEquip();
	void RemoveEquip() const;

	void ShowSkillW();
	void RemoveSillW() const;

	void ShowQuick(class UC_QuickSlotComponent* _QuickComponent);

	const UInventoryMenu* GetInvetoryWidget() { return InventoryWidget; }

private:
	TWeakObjectPtr<class US_StatComponent> SStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Exp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Lvl;

	UPROPERTY(meta = (BindWidget))
	UW_QuickSlotMenu* SkillSlot;

	UPROPERTY(meta = (BindWidget))
	UW_QuickSlotMenu* PotionSlot;

	TSubclassOf<UInventoryMenu> U_InventoryWidget;

	UInventoryMenu* InventoryWidget;

	TSubclassOf<UW_Equip> U_EquipmentWidget;

	UW_Equip* EquipmentWidget;

	TSubclassOf<UW_Skill> U_SkillWidget;

	UW_Skill* SkillWidget;
};
