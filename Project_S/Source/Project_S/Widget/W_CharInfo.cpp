// Fill out your copyright notice in the Description page of Project Settings.


#include "W_CharInfo.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Project_S/Component/S_StatComponent.h"

void UW_CharInfo::BindLvl(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnLvlChanged.AddUObject(this, &UW_CharInfo::UpdateLvl);
}

void UW_CharInfo::UpdateLvl()
{
	if (SStatComponent.IsValid())
		Txt_Lvl->SetText(FText::FromString(FString::Printf(TEXT("Lv : %d"), SStatComponent->GetLevel())));
}

void UW_CharInfo::BindHp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &UW_CharInfo::UpdateHp);
}

void UW_CharInfo::UpdateHp()
{
	if (SStatComponent.IsValid())
		PB_Hp->SetPercent(SStatComponent->GetHpRatio());
}

void UW_CharInfo::BindMp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnMpChanged.AddUObject(this, &UW_CharInfo::UpdateMp);
}

void UW_CharInfo::UpdateMp()
{
	if (SStatComponent.IsValid())
		PB_Mp->SetPercent(SStatComponent->GetMpRatio());
}

void UW_CharInfo::BindExp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	_StatComp->OnExpChanged.AddUObject(this, &UW_CharInfo::UpdateExp);
}

void UW_CharInfo::UpdateExp()
{
	if (SStatComponent.IsValid())
		PB_Exp->SetPercent(SStatComponent->GetExpRatio());
}