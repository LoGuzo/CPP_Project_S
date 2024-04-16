// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"

// Sets default values
AFirstCharacter::AFirstCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AFirstCharacter::SetMyColor(int32 _MyColor)
{
	MyColor = _MyColor;
}

void AFirstCharacter::SetExp(int32 _Exp)
{
	Exp = _Exp;
}


