// Fill out your copyright notice in the Description page of Project Settings.


#include "W_BossHp.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Project_S/Component/S_StatComponent.h"

void UW_BossHp::BindHp(class US_StatComponent* _StatComp)
{
	StatComp = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &UW_BossHp::UpdateHp);
}

void UW_BossHp::UpdateHp()
{
	if (StatComp.IsValid())
	{
		PB_Hp->SetPercent(StatComp->GetHpRatio());
		Txt_Hp->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), (int)StatComp->GetHp(), (int)StatComp->GetMaxHp())));
	}
}

void UW_BossHp::SetTxtName(const int32 Lvl, const FString& Name)
{
	if (StatComp.IsValid())
		Txt_LvName->SetText(FText::FromString(FString::Printf(TEXT("LV.%d %s"), Lvl, *Name)));
}