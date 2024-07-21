// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CharacterWidget.h"
#include "DO_DragDrop.h"
#include "InventoryMenu.h"
#include "W_CharInfo.h"
#include "W_Equip.h"
#include "W_Skill.h"
#include "W_Respawn.h"
#include "W_QuestSystem.h"
#include "W_QuickSlotMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollection.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include "Project_S/Component/C_QuickSlotComponent.h"


US_CharacterWidget::US_CharacterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventoryMenu>Inven(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_InventoryMenu.WBP_InventoryMenu_C'"));
	if (Inven.Succeeded())
	{
		U_InventoryWidget = Inven.Class;
	}

	static ConstructorHelpers::FClassFinder<UW_Equip>Equip(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Equip.WBP_Equip_C'"));
	if (Equip.Succeeded())
	{
		U_EquipmentWidget = Equip.Class;
	}

	static ConstructorHelpers::FClassFinder<UW_Skill>Sk(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Skill.WBP_Skill_C'"));
	if (Sk.Succeeded())
	{
		U_SkillWidget = Sk.Class;
	}

	static ConstructorHelpers::FClassFinder<UW_Respawn>Respawn(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Respawn.WBP_Respawn_C'"));
	if (Respawn.Succeeded())
	{
		U_RespawnWidget = Respawn.Class;
	}
}

void US_CharacterWidget::ShowInventory()
{
	if (U_InventoryWidget) {
		InventoryWidget = CreateWidget<UInventoryMenu>(GetWorld(), U_InventoryWidget);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}
	}
}

void US_CharacterWidget::RemoveInventory() const
{
	if (InventoryWidget)
	{
		InventoryWidget->RemoveFromParent();
	}
}

void US_CharacterWidget::ShowEquip()
{
	if (U_EquipmentWidget) {
		EquipmentWidget = CreateWidget<UW_Equip>(GetWorld(), U_EquipmentWidget);
		if (EquipmentWidget)
		{
			EquipmentWidget->AddToViewport();
		}
	}
}

void US_CharacterWidget::RemoveEquip() const
{
	if (EquipmentWidget)
	{
		EquipmentWidget->RemoveFromParent();
	}
}

void US_CharacterWidget::ShowSkillW()
{
	if (U_SkillWidget) {
		SkillWidget = CreateWidget<UW_Skill>(GetWorld(), U_SkillWidget);
		if (SkillWidget)
		{
			SkillWidget->AddToViewport();
		}
	}
}

void US_CharacterWidget::RemoveSillW() const
{
	if (SkillWidget)
	{
		SkillWidget->RemoveFromParent();
	}
}

void US_CharacterWidget::ShowQuick(UC_QuickSlotComponent* _QuickComponent)
{
	QuickComponent = _QuickComponent;
	if (QuickComponent.IsValid())
	{
		SkillSlot->ShowQSkillWidget(QuickComponent.Get());
		PotionSlot->ShowQPotionWidget(QuickComponent.Get());
	}
	QuickComponent->OnQuickUpdated.AddUObject(this, &US_CharacterWidget::ShowQuickDynamic);
}

void US_CharacterWidget::ShowQuickDynamic()
{
	if (QuickComponent.IsValid())
	{
		SkillSlot->ShowQSkillWidget(QuickComponent.Get());
		PotionSlot->ShowQPotionWidget(QuickComponent.Get());
	}
}

void US_CharacterWidget::ShowRespawn(AUserCharacter* _UserCharacter)
{
	if (U_RespawnWidget)
	{
		RespawnWidget = CreateWidget<UW_Respawn>(GetWorld(), U_RespawnWidget);
		if (RespawnWidget)
		{
			RespawnWidget->AddToViewport();
			RespawnWidget->SetUser(_UserCharacter);
		}
	}
}

void US_CharacterWidget::RemoveRespawn() const
{
	if (RespawnWidget)
	{
		RespawnWidget->RemoveFromParent();
		RespawnWidget->SetUser(nullptr);
	}
}