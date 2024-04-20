// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CharacterWidget.h"
#include "S_StatComponent.h"
#include "Components/ProgressBar.h"

US_CharacterWidget::US_CharacterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventoryMenu>UW_Inven(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_InventoryMenu.WBP_InventoryMenu_C'"));
	if (UW_Inven.Succeeded())
	{
		U_InventoryWidget = UW_Inven.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget>UW_Equip(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Equip.WBP_Equip_C'"));
	if (UW_Equip.Succeeded())
	{
		U_EquipmentWidget = UW_Equip.Class;
	}
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

void US_CharacterWidget::RemoveInventory()
{
	if (InventoryWidget)
	{
		InventoryWidget->RemoveFromParent();
	}
}

void US_CharacterWidget::ShowEquip()
{
	if (U_EquipmentWidget) {
		EquipmentWidget = CreateWidget<UUserWidget>(GetWorld(), U_EquipmentWidget);
		if (EquipmentWidget)
		{
			EquipmentWidget->AddToViewport();
		}
	}
}

void US_CharacterWidget::RemoveEquip()
{
	if (EquipmentWidget)
	{
		EquipmentWidget->RemoveFromParent();
	}
}


