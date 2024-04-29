// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UserAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
/**
 * 
 */
UCLASS()
class PROJECT_S_API UUserAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UUserAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	FOnAttackHit OnAttackHit;
private:
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool HaveWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* OneHandSwordAM;

public:
	bool GetIsInAir() const { return IsInAir; }
	float GetSpeed() const { return Speed; }
	bool GetHaveWeapon() const { return HaveWeapon; }

	void SetIsInAir(const bool _IsInAir);
	void SetSpeed(const float _Speed);
	void SetHaveWeapon(const bool _HaveWeapon);

	void OnHandSwordPlayAM();
	void JumpToSection(int32 _SectionIndex);
	FName GetAttackMontageName(int32 _SectionIndex);


	UFUNCTION()
	void AnimNotify_AttackHit();
};
