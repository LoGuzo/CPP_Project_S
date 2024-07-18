// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Projectile.h"
#include "Projectile_Missle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AProjectile_Missle : public AS_Projectile
{
	GENERATED_BODY()
	
public:
	AProjectile_Missle();

	void SetTarget(FVector _Location, FVector _Target);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
private:
	bool StartMoving;

	FVector Target;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraSystem;

	virtual void Explode() override;

	void MoveTowardsTarget(float DeltaTime);
	void RotateTowardsTarget(float DeltaTime);

};
