// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAnimInstance.h"
#include "Project_S/Character/UserCharacter.h"
#include "Animation/AnimNode_StateMachine.h"
#include "Animation/AnimInstanceProxy.h"

UUserAnimInstance::UUserAnimInstance() : NowSkill(nullptr), Player(nullptr)
{
	Speed = 0.0f;
	HaveWeapon = false;
	OnDash = false;
	bIsHit = false;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK(TEXT("AnimMontage'/Game/Mannequin/Animations/OneHandSword_Attack_Montage.OneHandSword_Attack_Montage'"));
	if (ATTACK.Succeeded())
		OneHandSwordAM = ATTACK.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SATTACK(TEXT("AnimMontage'/Game/Mannequin/Animations/Infinity/Staff_Attack_Monatage.Staff_Attack_Monatage'"));
	if (SATTACK.Succeeded())
		OneHandStaffAM = SATTACK.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> WAKEUP(TEXT("AnimMontage'/Game/Mannequin/Animations/Infinity/WakeUp_Montage.WakeUp_Montage'"));
	if (WAKEUP.Succeeded())
		WakeUpAM = WAKEUP.Object;
}

UUserAnimInstance::~UUserAnimInstance()
{
	if (NowSkill != nullptr)
		NowSkill = nullptr;
}

void UUserAnimInstance::SetDirection(const float _Direction)
{
	Direction = _Direction;
}

void UUserAnimInstance::PlaySome(TSharedPtr<FSkillTable>_Data)
{
	NowSkill = _Data.Get();
	if (NowSkill->AnimMontage != nullptr)
	{
		if (!Montage_IsPlaying(NowSkill->AnimMontage))
			Montage_Play(NowSkill->AnimMontage);
	}
}

void UUserAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (::IsValid(Player))
		Speed = Player->GetVelocity().Size();
}

void UUserAnimInstance::ColliderNotify()
{
	switch (NowSkill->Type)
	{
	case E_SkillType::E_Melee:
		break;
	case E_SkillType::E_Scope:
		Player->ScopeAttackCheck(NowSkill->Range);
		break;
	case E_SkillType::E_Shot:
		Player->ShotAttackCheck();
		break;
	default:
		break;
	}
}

void UUserAnimInstance::AnyMoveNotify()
{
	if (NowSkill)
		Player->AnyMove(NowSkill->AnimCurve);
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

void UUserAnimInstance::SetIsHit(const bool _bIsHit)
{
	bIsHit = _bIsHit;
}

void UUserAnimInstance::OnHandSwordPlayAM()
{
	if (!Montage_IsPlaying(OneHandSwordAM))
		Montage_Play(OneHandSwordAM, 1.f);
}

void UUserAnimInstance::OnHandStaffPlayAM()
{
	if (!Montage_IsPlaying(OneHandStaffAM))
		Montage_Play(OneHandStaffAM, 1.f);
}

void UUserAnimInstance::WakeUpPlayAM()
{
	if (!Montage_IsPlaying(WakeUpAM))
		Montage_Play(WakeUpAM);
}

void UUserAnimInstance::JumpToSection(int32 _SectionIndex, int32 Class)
{
	FName Name = GetAttackMontageName(_SectionIndex);
	switch (Class)
	{
	case 0:
		Montage_JumpToSection(Name, OneHandSwordAM);
		break;
	case 1:
		Montage_JumpToSection(Name, OneHandStaffAM);
		break;
	default:
		break;
	}
}

FName UUserAnimInstance::GetAttackMontageName(int32 _SectionIndex)
{
	return FName(FString::Printf(TEXT("Attack%d"), _SectionIndex));
}

void UUserAnimInstance::SetPlayer(AUserCharacter* _Player)
{
	Player = _Player;
}

void UUserAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}

void UUserAnimInstance::AnimNotify_Collider()
{
	ColliderNotify();
}

void UUserAnimInstance::AnimNotify_AnyMove()
{
	AnyMoveNotify();
}

void UUserAnimInstance::AnimNotify_Shot()
{
	Player->ShotAttackCheck();
}
