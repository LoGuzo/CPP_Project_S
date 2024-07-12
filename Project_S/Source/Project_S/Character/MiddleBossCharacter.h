// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MiddleBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AMiddleBossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AMiddleBossCharacter();

	virtual void LoadCharacterData() override;

	virtual void ShowHpBar() override;
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TSubclassOf<class UW_BossHp> U_BossHp;
	class UW_BossHp* W_BossHp;

	UPROPERTY()
	FTimerHandle RemoveWidgetHandle;

	void RemoveWidget();
};
