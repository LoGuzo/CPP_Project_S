// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AEnemyCharacter : public AFirstCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	class UOnlyHpBar* OnlyHpBar;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

};
