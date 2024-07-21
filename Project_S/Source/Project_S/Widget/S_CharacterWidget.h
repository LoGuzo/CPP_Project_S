// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CharacterWidget.generated.h"

/**
 * 
 */

class UW_CharInfo;
class UInventoryMenu;
class UW_Equip;
class UW_Skill;
class UW_QuestSystem;
class UW_QuickSlotMenu;
class UC_QuickSlotComponent;
class UW_Respawn;
class AUserCharacter;

UCLASS()
class PROJECT_S_API US_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	US_CharacterWidget(const FObjectInitializer& ObjectInitializer);

	void ShowInventory();
	void RemoveInventory() const;

	void ShowEquip();
	void RemoveEquip() const;

	void ShowSkillW();
	void RemoveSillW() const;

	void ShowQuick(UC_QuickSlotComponent* _QuickComponent);
	void ShowQuickDynamic();

	void ShowRespawn(AUserCharacter* _UserCharacter);
	void RemoveRespawn() const;

	const UInventoryMenu* GetInvetoryWidget() { return InventoryWidget; }

	const UW_QuickSlotMenu* GetQuickWidget() { return PotionSlot; }

	UW_CharInfo* GetCharInfo() { return WBP_CharInfo; }

	UW_QuestSystem* GetQuestSystem() { return WBP_QuestSystem; }

private:
	class UDO_DragDrop* DO_Drag;
	TWeakObjectPtr<UC_QuickSlotComponent> QuickComponent;

	UPROPERTY(meta = (BindWidget))
	UW_QuickSlotMenu* SkillSlot;

	UPROPERTY(meta = (BindWidget))
	UW_QuickSlotMenu* PotionSlot;

	UPROPERTY(meta = (BindWidget))
	UW_CharInfo* WBP_CharInfo;

	UPROPERTY(meta = (BindWidget))
	UW_QuestSystem* WBP_QuestSystem;

	TSubclassOf<UInventoryMenu> U_InventoryWidget;

	UInventoryMenu* InventoryWidget;

	TSubclassOf<UW_Equip> U_EquipmentWidget;

	UW_Equip* EquipmentWidget;

	TSubclassOf<UW_Skill> U_SkillWidget;

	UW_Skill* SkillWidget;

	TSubclassOf<UW_Respawn> U_RespawnWidget;

	UW_Respawn* RespawnWidget;
};
