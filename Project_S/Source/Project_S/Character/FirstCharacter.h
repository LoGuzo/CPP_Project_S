// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstCharacter.generated.h"

enum class E_CharacterType
{
	E_Monster,
	E_User,
	E_Npc,
};

UCLASS()
class PROJECT_S_API AFirstCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstCharacter();

private:
	UPROPERTY(Replicated, VisibleAnywhere)
	FString CharID;

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	E_CharacterType MyCharType;

	FVector SaveLocation;

	virtual void ResetStat() {};

	UPROPERTY(Replicated, VisibleAnywhere)
	class US_StatComponent* Stat;

	UPROPERTY(VisibleAnywhere)
	class UC_SkillComponent* Skill;

	bool IsDead;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundWave* ParticleSound;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* HitParticleEffect;

public:
	bool IsAttacking;

	class US_StatComponent* GetStatCom() { return Stat; }
	class UC_SkillComponent* GetSkillCom() { return Skill; }

	virtual void UseSkill(const FString& _SkillName);


	void MeleeAttackCheck(float _Range);

	void ScopeAttackCheck(float _Range);

	virtual void ShotAttackCheck();

	FString GetCharID() { return CharID; }

	void SetCharID(const FString& _CharID);

	void SetSaveLocation(FVector _SaveLocation);
	FVector GetSaveLocation() { return SaveLocation; }

	bool GetIsDead() { return IsDead; }

	E_CharacterType GetType() { return MyCharType; }

protected:
	UFUNCTION(Server, Reliable, WithValidation)
	virtual void Server_UseSkill(const FString& _SkillName);

	UFUNCTION(NetMulticast, Reliable)
	virtual void Multi_UseSkill(const FString& _SkillName);

	virtual void Multi_UseSkill_Implementation(const FString& SkillName);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
