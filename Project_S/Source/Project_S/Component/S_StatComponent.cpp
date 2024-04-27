// Fill out your copyright notice in the Description page of Project Settings.


#include "S_StatComponent.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
US_StatComponent::US_StatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bWantsInitializeComponent = true;
}


// Called when the game starts
void US_StatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetLevel(Level);
}

void US_StatComponent::SetLevel(int32 _Level)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (_Level != 0) {
			auto StatData = static_cast<FCharacterData*>(MyGameInstance->MyDataManager.FindRef("CharData")->GetMyData(*FString::FromInt(_Level)));
			if (StatData)
			{
				Level = StatData->Level;
				SetHp(StatData->MaxHp);
				MaxHp = StatData->MaxHp;
				SetMp(StatData->MaxMp);
				MaxMp = StatData->MaxMp;
				MaxExp = StatData->MaxExp;
				SetExp(0);
				Attack = StatData->Attack;
				Armor = StatData->Armor;
			}
		}
	}
}

void US_StatComponent::SetHp(int32 _Hp)
{
	Hp = _Hp;
	if (Hp < 0)
		Hp = 0;

	OnHpChanged.Broadcast();
}

void US_StatComponent::SetMp(int32 _Mp)
{
	Mp = _Mp;
	if (Mp < 0)
		Mp = 0;

	OnMpChanged.Broadcast();
}

void US_StatComponent::SetExp(int32 _Exp)
{
	Exp = _Exp;
	if (Exp >= MaxExp)
		SetLevel(Level+1);

	OnExpChanged.Broadcast();
}

void US_StatComponent::OnAttacked(float DamageAmount)
{
	int32 hp = Hp - DamageAmount;
	SetHp(hp);
}


