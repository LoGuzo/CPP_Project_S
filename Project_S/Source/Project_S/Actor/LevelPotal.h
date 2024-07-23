// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPotal.generated.h"

UCLASS()
class PROJECT_S_API ALevelPotal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelPotal();
	void SetLevelName(const FString& _LevelName);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	FTimerHandle UnusedHandle;
public:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString LevelName;

	UPROPERTY()
	class UBoxComponent* BoxCollision;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION()
	void BPFunction();

	void NextLevel();

	UPROPERTY()
	class UParticleSystem* Particle;
	class UParticleSystemComponent* ParticleComponent;
};
