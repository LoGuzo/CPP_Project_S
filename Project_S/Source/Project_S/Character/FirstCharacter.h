// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_S/Component/S_StatComponent.h"
#include "FirstCharacter.generated.h"

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

public:
	int32 GetMyColor() { return MyColor; }
	FString GetCharID() { return CharID; }
	void SetMyColor(int32 _MyColor);
	void SetCharID(FString _CharID);

	UPROPERTY(VisibleAnywhere)
	US_StatComponent* Stat;
};
