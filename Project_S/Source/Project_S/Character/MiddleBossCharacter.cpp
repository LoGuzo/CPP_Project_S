// Fill out your copyright notice in the Description page of Project Settings.


#include "MiddleBossCharacter.h"
#include "Project_S/Widget/W_BossHp.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Controllers/UserPlayerController.h"

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

	if (Stat) {
		if (Stat->GetHp() <= 0)
		{
			FTimerDelegate TimerDel;
			TimerDel.BindUFunction(this, FName("SyncRemoveWidget"), EventInstigator);
			GetWorldTimerManager().SetTimer(RemoveWidgetHandle, TimerDel, 10.f, false);
		}
	}
	return DamageAmount;
}

void AMiddleBossCharacter::ShowHpBar()
{
	if (W_BossHp && !W_BossHp->IsInViewport())
	{
		W_BossHp->SetTxtName(Stat->GetLevel(), GetCharID());
		W_BossHp->UpdateHp();
		W_BossHp->AddToViewport();
	}
}

void AMiddleBossCharacter::LoadCharacterData()
{
	Super::LoadCharacterData();
}


void AMiddleBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	W_BossHp = CreateWidget<UW_BossHp>(GetWorld(), U_BossHp);
	if (W_BossHp)
	{
		if (Stat)
		{
			W_BossHp->BindHp(Stat);
		}
	}
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
	}
}

void AMiddleBossCharacter::SyncRemoveWidget(AController* PlayerController)
{
	AUserPlayerController* UserPlayerController = Cast<AUserPlayerController>(PlayerController);
	if (UserPlayerController)
	{
		UserPlayerController->SyncRemoveEnemyHpBar(this);
	}
}