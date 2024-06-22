// Fill out your copyright notice in the Description page of Project Settings.


#include "W_CharInfo.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Project_S/Component/S_StatComponent.h"

void UW_CharInfo::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetTimerManager().ClearTimer(ShakeTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(EndShakeHandle);
	GetWorld()->GetTimerManager().ClearTimer(HealthUpdateTimerHandle);
}

void UW_CharInfo::BindLvl(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	SStatComponent->OnLvlChanged.AddUObject(this, &UW_CharInfo::UpdateLvl);
}

void UW_CharInfo::UpdateLvl()
{
	if (SStatComponent.IsValid())
		Txt_Lvl->SetText(FText::FromString(FString::Printf(TEXT("Lv : %d"), SStatComponent->GetLevel())));
}

void UW_CharInfo::SetImg(UTexture2D* ClassImg)
{
	Img_Char->SetBrushFromTexture(ClassImg);
}

void UW_CharInfo::BindHp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	SStatComponent->OnHpChanged.AddUObject(this, &UW_CharInfo::UpdateHp);
}

void UW_CharInfo::UpdateHp()
{
	if (SStatComponent.IsValid())
	{
		TargetHealth = SStatComponent->GetHpRatio();
		CurrentHealth = PB_Hp->Percent;
		HealthUpdateDuration = 1.f;
		HealthUpdateTime = 0.f;
	}
	GetWorld()->GetTimerManager().SetTimer(HealthUpdateTimerHandle, this, &UW_CharInfo::AnimateHealthBar, 0.016f, true);
}

void UW_CharInfo::BindMp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	SStatComponent->OnMpChanged.AddUObject(this, &UW_CharInfo::UpdateMp);
}

void UW_CharInfo::UpdateMp()
{
	if (SStatComponent.IsValid())
		PB_Mp->SetPercent(SStatComponent->GetMpRatio());
}

void UW_CharInfo::BindExp(class US_StatComponent* _StatComp)
{
	SStatComponent = _StatComp;
	SStatComponent->OnExpChanged.AddUObject(this, &UW_CharInfo::UpdateExp);
}

void UW_CharInfo::UpdateExp()
{
	if (SStatComponent.IsValid())
		PB_Exp->SetPercent(SStatComponent->GetExpRatio());
}

void UW_CharInfo::ShakeHealthBar()
{
	FVector2D OriginalPosition = PB_Hp->RenderTransform.Translation;
	float ShakeAmount = 5.0f;
	float ShakeSpeed = 10.0f;

	GetWorld()->GetTimerManager().SetTimer(ShakeTimerHandle, [this, OriginalPosition, ShakeAmount, ShakeSpeed]()
		{
			FVector2D ShakeOffset = FVector2D(FMath::Sin(GetWorld()->GetTimeSeconds() * ShakeSpeed) * ShakeAmount, 0.0f);
			PB_Hp->SetRenderTranslation(OriginalPosition + ShakeOffset);
		}, 0.016f, true);

	GetWorld()->GetTimerManager().SetTimer(EndShakeHandle, [this, OriginalPosition]()
		{
			GetWorld()->GetTimerManager().ClearTimer(ShakeTimerHandle);
			PB_Hp->SetRenderTranslation(OriginalPosition);
		}, 0.5f, false);
}

void UW_CharInfo::AnimateHealthBar()
{
	HealthUpdateTime += GetWorld()->GetDeltaSeconds();

	if (HealthUpdateTime >= HealthUpdateDuration)
	{
		GetWorld()->GetTimerManager().ClearTimer(HealthUpdateTimerHandle);
		PB_Hp->SetPercent(TargetHealth);
		CurrentHealth = TargetHealth;
	}
	else
	{
		float Alpha = FMath::Clamp(HealthUpdateTime / HealthUpdateDuration, 0.0f, 1.0f);
		float NewHealth = FMath::Lerp(CurrentHealth, TargetHealth, Alpha);
		PB_Hp->SetPercent(NewHealth);
	}
}