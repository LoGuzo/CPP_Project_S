// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstCharacter.generated.h"

UCLASS()
class PROJECT_S_API AFirstCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstCharacter();

private:
	int32 Level;
	int32 Hp;
	int32 Mp;
	int32 MyColor;
	int32 Type;
	int32 Exp;

public:
	int32 GetLevel() { return Level; }
	int32 GetHp() { return Hp; }
	int32 GetMp() { return Mp; }
	int32 GetMyColor() { return MyColor; }
	int32 GetType() { return Type; }
	int32 GetExp() { return Exp; }
	void SetMyColor(int32 _MyColor);
	void SetExp(int32 _Exp);
};
