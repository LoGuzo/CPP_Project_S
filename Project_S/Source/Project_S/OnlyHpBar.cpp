// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlyHpBar.h"
#include "S_StatComponent.h"
#include "Components/ProgressBar.h"

void UOnlyHpBar::BindHp(class US_StatComponent* _StatComp)
{
	StatComp = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &UOnlyHpBar::UpdateHp);
}

void UOnlyHpBar::UpdateHp()
{
	if (StatComp.IsValid())
		PB_Hp->SetPercent(StatComp->GetHpRatio());
}