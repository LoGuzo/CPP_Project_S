// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnMpChanged);
DECLARE_MULTICAST_DELEGATE(FOnExpChanged);
DECLARE_MULTICAST_DELEGATE(FOnLvlChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API US_StatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US_StatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	FOnHpChanged OnHpChanged;
	FOnMpChanged OnMpChanged;
	FOnExpChanged OnExpChanged;
	FOnLvlChanged OnLvlChanged;

	void SetLevel(int32 _Level);
	void SetHp(float _Hp);
	void SetMp(float _Mp);
	void SetExp(float _Exp);
	void OnAttacked(float DamageAmount);

	int32 GetLevel() { return Level; }
	float GetHp() { return Hp; }
	float GetMaxHp() { return MaxHp; }
	float GetHpRatio() { return Hp / MaxHp; }
	float GetMp() { return Mp; }
	float GetMaxMp() { return MaxMp; }
	float GetMpRatio() { return Mp / MaxMp; }
	float GetExp() { return Exp; }
	float GetMaxExp() { return MaxExp; }
	float GetExpRatio() { return Exp / MaxExp; }	
	float GetArmor() { return Armor; }
	float GetAttack() { return Attack; }

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	// Hp
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Hp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float MaxHp;

	// Mp
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Mp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float MaxMp;

	// Exp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Exp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float MaxExp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Armor;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Attack;

		
};
