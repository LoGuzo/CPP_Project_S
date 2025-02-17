// Fill out your copyright notice in the Description page of Project Settings.


#include "S_StatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Instance/S_GameInstance.h"

// Sets default values for this component's properties
US_StatComponent::US_StatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
	bWantsInitializeComponent = true;
	Level = 3;
}


// Called when the game starts
void US_StatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetLevel(Level);
}

void US_StatComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (StatData != nullptr)
		StatData.Reset();
}

void US_StatComponent::SetLevel(int32 _Level)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (_Level != 0) {
			StatData = StaticCastSharedPtr<FCharacterData>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_Char)->GetMyData(*FString::FromInt(_Level)));
			if (StatData.IsValid())
			{
				MaxLevel = 3;
				Level = StatData.Pin()->Level;
				SetHp(StatData.Pin()->MaxHp);
				MaxHp = StatData.Pin()->MaxHp;
				SetMp(StatData.Pin()->MaxMp);
				MaxMp = StatData.Pin()->MaxMp;
				MaxExp = StatData.Pin()->MaxExp;
				SetExp(0);
				Attack = StatData.Pin()->Attack;
				Armor = StatData.Pin()->Armor;
			}
		}
	}
	OnLvlChanged.Broadcast();
}

void US_StatComponent::SetMonsterLevel(int32 _Level)
{
	Level = _Level;
}

void US_StatComponent::SetHp_Implementation(float _Hp)
{
	Hp = _Hp;
	if (Hp < 0)
		Hp = 0;
	OnHpChanged.Broadcast();
}

void US_StatComponent::SetMaxHp_Implementation(float _MaxHp)
{
	MaxHp = _MaxHp;
}

void US_StatComponent::SetMp(float _Mp)
{
	Mp = _Mp;
	if (Mp < 0)
		Mp = 0;

	OnMpChanged.Broadcast();
}

void US_StatComponent::SetMaxMp(float _MaxMp)
{
	MaxMp = _MaxMp;
}

void US_StatComponent::SetExp(float _Exp)
{
	if (Level < MaxLevel)
	{
		Exp = _Exp;
		if (Exp >= MaxExp)
			SetLevel(Level + 1);
	}
	else
	{
		Exp = 0;
	}

	OnExpChanged.Broadcast();
}

void US_StatComponent::SetMaxExp(float _MaxExp)
{
	MaxExp = _MaxExp;
}

void US_StatComponent::OnAttacked(float DamageAmount)
{
	float hp = Hp - DamageAmount;
	SetHp(hp);
}

void US_StatComponent::SetArmor(float _Armor)
{
	Armor = _Armor;
}

void US_StatComponent::SetAttack(float _Attack)
{
	Attack = _Attack;
}

void US_StatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(US_StatComponent, Hp);
	DOREPLIFETIME(US_StatComponent, MaxHp);
	DOREPLIFETIME(US_StatComponent, Level);
}