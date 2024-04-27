// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"
#include "Project_S/Component/S_StatComponent.h"

// Sets default values
AFirstCharacter::AFirstCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Stat = CreateDefaultSubobject<US_StatComponent>(TEXT("STAT"));
}

float AFirstCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);

	return DamageAmount;
}

void AFirstCharacter::SetMyColor(int32 _MyColor)
{
	MyColor = _MyColor;
}

void AFirstCharacter::SetCharID(FString _CharID)
{
	CharID = _CharID;
}


