// Fill out your copyright notice in the Description page of Project Settings.


#include "W_CharInfo.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Instance/S_GameInstance.h"

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

void UW_CharInfo::SetImg(E_CharClass CharClass)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto ClassData = StaticCastSharedPtr<FCharacterClass>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_CharClassData)->GetMyData(CharMap.FindRef(CharClass)));
		if (ClassData.IsValid())
			Img_Char->SetBrushFromTexture(ClassData.Get()->Img_Class);
	}
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
	if (Shake_Hp)
		PlayAnimation(Shake_Hp);
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