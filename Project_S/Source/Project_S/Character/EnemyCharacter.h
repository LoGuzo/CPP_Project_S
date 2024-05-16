// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "Project_S/S_StructureAll.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
class UC_SkillComponent;
UCLASS()
class PROJECT_S_API AEnemyCharacter : public AFirstCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();
	virtual void UseSkill(FString _SkillName) override;
	UC_SkillComponent* GetPattern() { return Pattern; }
private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	class UOnlyHpBar* OnlyHpBar;

	class UMonsterAnimInstance* AnimInstance;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UC_SkillComponent* Pattern;

};
