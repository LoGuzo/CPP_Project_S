// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_SGameMode.h"
#include "BossGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ABossGameMode : public AProject_SGameMode
{
	GENERATED_BODY()

public:
	ABossGameMode();

	virtual void MonsterFactory() override;

protected:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayLevelSequence();

	void PlayCinematic();

	class ULevelSequence* BossSequence;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	UFUNCTION()
	void OnCinematicFinished();
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetDelegate();

private:
	UFUNCTION()
	void BossDied();

	TSubclassOf<class AActor> PotalBP;

	void ActivateSlowMotion(float SlowMotionTime, float Duration); // 슬로우 모션함수

	FTimerHandle ResetTimer;

	void ResetSlowMotion(); // 되돌리기

	TArray<class APlayerController*> ConnectedPlayers;

	void DelayedStart();

	class ABossCharacter* BossCharacter;
};
