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
	void SetHp(int32 _Hp);
	void SetMp(int32 _Mp);
	void SetExp(int32 _Exp);
	void OnAttacked(float DamageAmount);

	int32 GetLevel() { return Level; }
	int32 GetHp() { return Hp; }
	int32 GetMaxHp() { return MaxHp; }
	float GetHpRatio() { return Hp / (float)MaxHp; }
	int32 GetMp() { return Mp; }
	int32 GetMaxMp() { return MaxMp; }
	float GetMpRatio() { return Mp / (float)MaxMp; }
	int32 GetExp() { return Exp; }
	int32 GetMaxExp() { return MaxExp; }
	float GetExpRatio() { return Exp / (float)MaxExp; }	
	int32 GetArmor() { return Armor; }
	int32 GetAttack() { return Attack; }

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	// Hp
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	// Mp
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Mp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxMp;

	// Exp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxExp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Armor;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

		
};
