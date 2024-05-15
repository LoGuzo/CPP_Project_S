// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_S/Component/S_StatComponent.h"
#include "FirstCharacter.generated.h"

enum class E_CharacterType
{
	E_Monster,
	E_User,
	E_Npc,
};

UCLASS()
class PROJECT_S_API AFirstCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstCharacter();

private:
	int32 MyColor;
	FString CharID;

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	E_CharacterType MyCharType;
public:
	virtual void UseSkill() {};

	void MeleeAttackCheck(float _Range);
	void ScopeAttackCheck(float _Range);
	void ShotAttackCheck();

	int32 GetMyColor() { return MyColor; }
	FString GetCharID() { return CharID; }
	void SetMyColor(int32 _MyColor);
	void SetCharID(FString _CharID);

	UPROPERTY(VisibleAnywhere)
	US_StatComponent* Stat;
};
