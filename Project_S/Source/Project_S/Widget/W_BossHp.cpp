// Fill out your copyright notice in the Description page of Project Settings.


#include "W_BossHp.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Project_S/Component/S_StatComponent.h"

void UW_BossHp::NativeDestruct()
{
    Super::NativeDestruct();
    GetWorld()->GetTimerManager().ClearTimer(HealthUpdateTimerHandle);
}

void UW_BossHp::BindHp(class US_StatComponent* _StatComp)
{
	StatComp = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &UW_BossHp::UpdateHp);
}

void UW_BossHp::UpdateHp()
{
	if (StatComp.IsValid())
	{
        UE_LOG(LogTemp, Warning, TEXT("%f"), StatComp->GetHp());
        TargetHealth = StatComp->GetHpRatio();
        CurrentHealth = PB_Hp->Percent;
        HealthUpdateDuration = 1.f;
        HealthUpdateTime = 0.f;
		Txt_Hp->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), (int)StatComp->GetHp(), (int)StatComp->GetMaxHp())));
	}
    GetWorld()->GetTimerManager().SetTimer(HealthUpdateTimerHandle, this, &UW_BossHp::AnimateHealthBar, 0.016f, true);
}

void UW_BossHp::SetTxtName(const int32 Lvl, const FString& Name)
{
	if (StatComp.IsValid())
		Txt_LvName->SetText(FText::FromString(FString::Printf(TEXT("LV.%d %s"), Lvl, *Name)));
}


void UW_BossHp::AnimateHealthBar()
{
    HealthUpdateTime += GetWorld()->GetDeltaSeconds();
    if (HealthUpdateTime >= HealthUpdateDuration)
    {
        GetWorld()->GetTimerManager().ClearTimer(HealthUpdateTimerHandle);
        PB_Hp->SetPercent(TargetHealth);
    }
    else
    {
        float Alpha = HealthUpdateTime / HealthUpdateDuration;
        float NewHealth = FMath::Lerp(CurrentHealth, TargetHealth, Alpha);
        PB_Hp->SetPercent(NewHealth);
    }
}