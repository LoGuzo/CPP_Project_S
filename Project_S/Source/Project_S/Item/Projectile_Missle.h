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

	void SetTarget(AActor* TargetActor);
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
private:
	AActor* Target;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraSystem;
};
