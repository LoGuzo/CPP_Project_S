// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UserAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
/**
 * 
 */
class AUserCharacter;
struct FSkillTable;

UCLASS()
class PROJECT_S_API UUserAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UUserAnimInstance();
	~UUserAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	FOnAttackHit OnAttackHit;
private:
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool HaveWeapon;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool OnDash;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsHit;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* OneHandSwordAM;

	FSkillTable* NowSkill;

	AUserCharacter* Player;
public:
	float GetSpeed() const { return Speed; }
	bool GetHaveWeapon() const { return HaveWeapon; }

	void SetSpeed(const float _Speed);
	void SetHaveWeapon(const bool _HaveWeapon);

	bool GetOnDash() { return OnDash; }
	void SetOnDash(const bool _OnDash);

	bool GetIsHit() { return bIsHit; }
	void SetIsHit(const bool _bIsHit);

	float GetDirection() { return Direction; }
	void SetDirection(const float _Direction);

	void PlaySome(TSharedPtr<FSkillTable>_Data);
	void ColliderNotify();
	void AnyMoveNotify();

	void OnHandSwordPlayAM();
	void JumpToSection(int32 _SectionIndex);
	FName GetAttackMontageName(int32 _SectionIndex);

	void SetPlayer(AUserCharacter* _Player);

	UFUNCTION()
	void AnimNotify_AttackHit();

	UFUNCTION()
	void AnimNotify_Collider();

	UFUNCTION()
	void AnimNotify_AnyMove();
};
