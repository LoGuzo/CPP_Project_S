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

	UPROPERTY()
	class UParticleSystem* HitParticleEffect;

	UPROPERTY(Replicated, VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* ProjectileMesh;

	class AFirstCharacter* Owner;
	void ScopeAttackCheck(float _Range);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundWave* ParticleSound;

	void SetProjectileOwner(class AFirstCharacter* _Owner);

	virtual void SetProjectile() {};

	virtual void Explode() {};

	UFUNCTION(NetMulticast, Reliable)
	void SetParticle();

	//Decal 마법진과 같은 것을 사용할때

private:
	int32 Cnt;
	int32 MaxCnt;
	int32 Type;
};
