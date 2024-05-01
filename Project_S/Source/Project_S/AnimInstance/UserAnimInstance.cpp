// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Project_S/Character/UserCharacter.h"

UUserAnimInstance::UUserAnimInstance()
{
	Speed = 0.0f;
	HaveWeapon = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK(TEXT("AnimMontage'/Game/Mannequin/Animations/OneHandSword_Attack_Montage.OneHandSword_Attack_Montage'"));
	if (ATTACK.Succeeded())
	{
		OneHandSwordAM = ATTACK.Object;
	}
}

void UUserAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}

void UUserAnimInstance::SetSpeed(float _Speed)
{
	Speed = _Speed;
}

void UUserAnimInstance::SetHaveWeapon(bool _HaveWeapon)
{
	HaveWeapon = _HaveWeapon;
}

void UUserAnimInstance::SetOnDash(const bool _OnDash)
{
	OnDash = _OnDash;
}

void UUserAnimInstance::OnHandSwordPlayAM()
{
	if (!Montage_IsPlaying(OneHandSwordAM))
	{
		Montage_Play(OneHandSwordAM, 1.f);
	}
}

void UUserAnimInstance::JumpToSection(int32 _SectionIndex)
{
	FName Name = GetAttackMontageName(_SectionIndex);
	Montage_JumpToSection(Name, OneHandSwordAM);
}

FName UUserAnimInstance::GetAttackMontageName(int32 _SectionIndex)
{
	return FName(FString::Printf(TEXT("Attack%d"), _SectionIndex));
}

void UUserAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}
