// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAnimInstance.h"
#include "Project_S/Character/UserCharacter.h"

UUserAnimInstance::UUserAnimInstance() : NowSkill(nullptr), Player(nullptr)
{
	Speed = 0.0f;
	HaveWeapon = false;
	OnDash = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK(TEXT("AnimMontage'/Game/Mannequin/Animations/OneHandSword_Attack_Montage.OneHandSword_Attack_Montage'"));
	if (ATTACK.Succeeded())
	{
		OneHandSwordAM = ATTACK.Object;
	}
}

void UUserAnimInstance::PlaySome(FSkillTable& _Data)
{
	NowSkill = &_Data;
	if (NowSkill->AnimMontage != nullptr)
	{
		if (!Montage_IsPlaying(NowSkill->AnimMontage))
		{
			Montage_Play(NowSkill->AnimMontage);
		}
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
	if (NowSkill != nullptr)
	{
		if (Montage_IsPlaying(NowSkill->AnimMontage))
		{
			int32 size = NotifyQueue.AnimNotifies.Num();
			if (size <= 0) return;
			for (int32 i = 0; i < size; i++)
			{
				FName name = NotifyQueue.AnimNotifies[i].GetNotify()->NotifyName;
				if (name == TEXT("Collider"))
				{
					if (Player != nullptr)
					{
						ColliderNotify();
					}
				}
				else if (name == TEXT("AnyMove"))
				{
					if (Player != nullptr)
					{
						AnyMoveNotify();
					}
				}
			}
		}
		else
			NowSkill = nullptr;
	}

}

void UUserAnimInstance::ColliderNotify()
{
	UE_LOG(LogTemp, Warning, TEXT("Collider Activated"));

	switch (NowSkill->Type)
	{
	case E_SkillType::E_Melee:
		break;
	case E_SkillType::E_Scope:
		break;
	case E_SkillType::E_Shot:
		break;
	default:
		break;
	}
}

void UUserAnimInstance::AnyMoveNotify()
{
	if (NowSkill)
	{
		Player->AnyMove(NowSkill->AnimCurve);
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

void UUserAnimInstance::SetPlayer(AUserCharacter* _Player)
{
	Player = _Player;
}

void UUserAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}
