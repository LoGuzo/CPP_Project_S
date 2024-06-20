// Fill out your copyright notice in the Description page of Project Settings.


#include "MiddleBossCharacter.h"
#include "Project_S/Widget/W_BossHp.h"
#include "Project_S/Component/S_StatComponent.h"

AMiddleBossCharacter::AMiddleBossCharacter()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_BossHP.WBP_BossHp_C'"));
	if (UW.Succeeded())
	{
		U_BossHp = UW.Class;
	}
}

float AMiddleBossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (W_BossHp && !W_BossHp->IsInViewport())
	{
		W_BossHp->AddToViewport();
	}
	if (Stat) {
		if (Stat->GetHp() <= 0)
		{
			GetWorldTimerManager().SetTimer(RemoveWidgetHandle, this, &AMiddleBossCharacter::RemoveWidget, 10.f, false);
		}
	}
	return DamageAmount;
}

void AMiddleBossCharacter::LoadCharacterData()
{
	Super::LoadCharacterData();
	if (W_BossHp)
	{
		if (Stat)
		{
			W_BossHp->BindHp(Stat);
			W_BossHp->SetTxtName(Stat->GetLevel(), GetCharID());
		}
	}
}

void AMiddleBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	W_BossHp = CreateWidget<UW_BossHp>(GetWorld(), U_BossHp);
}

void AMiddleBossCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(RemoveWidgetHandle);
}

void AMiddleBossCharacter::RemoveWidget()
{
	if (W_BossHp && W_BossHp->IsInViewport())
	{
		W_BossHp->RemoveFromViewport();
		W_BossHp = nullptr;
	}
}
