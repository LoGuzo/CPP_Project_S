// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CharacterWidget.h"
#include "S_StatComponent.h"
#include "Components/ProgressBar.h"

US_CharacterWidget::US_CharacterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventoryMenu>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_InventoryMenu.WBP_InventoryMenu_C'"));
	if (UW.Succeeded())
	{
		InventoryWidget = UW.Class;
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
	if (InventoryWidget) {
		inventoryWidget = CreateWidget<UInventoryMenu>(GetWorld(), InventoryWidget);
		if (inventoryWidget)
		{
			inventoryWidget->AddToViewport();
		}
	}
}

void US_CharacterWidget::RemoveInventory()
{
	if (inventoryWidget)
	{
		inventoryWidget->RemoveFromParent();
	}
}
