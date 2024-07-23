// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnMpChanged);
DECLARE_MULTICAST_DELEGATE(FOnExpChanged);
DECLARE_MULTICAST_DELEGATE(FOnLvlChanged);

struct FCharacterData;

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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	FOnHpChanged OnHpChanged;
	FOnMpChanged OnMpChanged;
	FOnExpChanged OnExpChanged;
	FOnLvlChanged OnLvlChanged;

	void SetLevel(int32 _Level);
	int32 GetLevel() { return Level; }

	void SetMonsterLevel(int32 _Level);

	UFUNCTION(NetMultiCast, Reliable)
	void SetHp(float _Hp);
	float GetHp() { return Hp; }

	UFUNCTION(NetMultiCast, Reliable)
	void SetMaxHp(float _MaxHp);
	float GetMaxHp() { return MaxHp; }

	void SetMp(float _Mp);
	float GetMp() { return Mp; }

	void SetMaxMp(float _MaxMp);
	float GetMaxMp() { return MaxMp; }

	void SetExp(float _Exp);
	float GetExp() { return Exp; }

	void SetMaxExp(float _MaxExp);
	float GetMaxExp() { return MaxExp; }
	void OnAttacked(float DamageAmount);
	void SetArmor(float _Armor);
	float GetArmor() { return Armor; }

	void SetAttack(float _Attack);
	float GetAttack() { return Attack; }

	float GetHpRatio() { return Hp / MaxHp; }
	float GetMpRatio() { return Mp / MaxMp; }
	float GetExpRatio() { return Exp / MaxExp; }	

private:
	// Level
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxLevel;

	UPROPERTY(Replicated, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	// Hp
	UPROPERTY(Replicated, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Hp;

	UPROPERTY(Replicated, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
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

	TWeakPtr<FCharacterData> StatData;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
