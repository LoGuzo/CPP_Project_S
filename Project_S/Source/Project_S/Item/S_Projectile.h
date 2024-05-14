// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Projectile.generated.h"

UCLASS()
class PROJECT_S_API AS_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	//Decal 마법진과 같은 것을 사용할때

private:
	int32 Cnt;
	int32 MaxCnt;
	int32 Type;

public:

	void FireInDirection(const FVector& Direction);
	virtual void SetProjectile();

};
