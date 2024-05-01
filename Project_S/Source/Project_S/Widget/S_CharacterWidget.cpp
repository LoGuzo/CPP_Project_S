// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CharacterWidget.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

US_CharacterWidget::US_CharacterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventoryMenu>UW_Inven(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_InventoryMenu.WBP_InventoryMenu_C'"));
	if (UW_Inven.Succeeded())
	{
		U_InventoryWidget = UW_Inven.Class;
	}
	static ConstructorHelpers::FClassFinder<UW_Equip>UW_Equip(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Equip.WBP_Equip_C'"));
	if (UW_Equip.Succeeded())
	{
		U_EquipmentWidget = UW_Equip.Class;
	}
	static ConstructorHelpers::FClassFinder<UW_Skill>UW_Sk(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Skill.WBP_Skill_C'"));
	if (UW_Sk.Succeeded())
	{
		U_SkillWidget = UW_Sk.Class;
	}
}

void US_CharacterWidget::BindLvl (class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnLvlChanged.AddUObject(this, &US_CharacterWidget::UpdateLvl);
}

void US_CharacterWidget::UpdateLvl()
{
	if (SStatComponent.IsValid())
		Txt_Lvl->SetText(FText::FromString(FString::Printf(TEXT("Lv : %d"), SStatComponent->GetLevel())));
}

void US_CharacterWidget::BindHp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &US_CharacterWidget::UpdateHp);
}

void US_CharacterWidget::UpdateHp()
{
	if (SStatComponent.IsValid())
		PB_Hp->SetPercent(SStatComponent->GetHpRatio());
}

void US_CharacterWidget::BindMp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnMpChanged.AddUObject(this, &US_CharacterWidget::UpdateMp);
}

void US_CharacterWidget::UpdateMp()
{
	if (SStatComponent.IsValid())
		PB_Mp->SetPercent(SStatComponent->GetMpRatio());
}

void US_CharacterWidget::BindExp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnExpChanged.AddUObject(this, &US_CharacterWidget::UpdateExp);
}

void US_CharacterWidget::UpdateExp()
{
	if (SStatComponent.IsValid())
		PB_Exp->SetPercent(SStatComponent->GetExpRatio());
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


