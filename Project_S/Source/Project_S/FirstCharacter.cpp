// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"
#include "S_StatComponent.h"

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
	Hp = Stat->GetHp();

	return DamageAmount;
}

void AFirstCharacter::SetMyColor(int32 _MyColor)
{
	MyColor = _MyColor;
}

void AFirstCharacter::SetExp(int32 _Exp)
{
	Exp = _Exp;
}


