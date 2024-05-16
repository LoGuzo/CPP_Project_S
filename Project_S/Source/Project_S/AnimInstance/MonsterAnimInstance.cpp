// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Project_S/Character/EnemyCharacter.h"

UMonsterAnimInstance::UMonsterAnimInstance() : NowPattern(nullptr), Monster(nullptr)
{
	Speed = 0.0f;
}

UMonsterAnimInstance::~UMonsterAnimInstance()
{
	if (NowPattern.IsValid())
	{
		NowPattern.Reset();
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (::IsValid(Monster))
	{
		Speed = Monster->GetVelocity().Size();
	}
}

void UMonsterAnimInstance::PlaySome(TWeakPtr<FMonsterPattern>_Data)
{
	NowPattern = _Data;
	if (NowPattern.Pin()->AnimMontage != nullptr)
	{
		if (!Montage_IsPlaying(NowPattern.Pin()->AnimMontage))
		{
			Montage_Play(NowPattern.Pin()->AnimMontage, 1.f);
		}
	}
}

void UMonsterAnimInstance::ColliderNotify()
{
	switch (NowPattern.Pin()->PatternType)
	{
	case E_SkillType::E_Melee:
		Monster->MeleeAttackCheck(NowPattern.Pin()->Range);
		break;
	case E_SkillType::E_Scope:
		Monster->ScopeAttackCheck(NowPattern.Pin()->Range);
		break;
	case E_SkillType::E_Shot:
		break;
	default:
		break;
	}
}

void UMonsterAnimInstance::SetSpeed(const float _Speed)
{
	Speed = _Speed;
}

void UMonsterAnimInstance::SetMonster(AEnemyCharacter* _Monster)
{
	Monster = _Monster;
}

void UMonsterAnimInstance::AnimNotify_Collider()
{
	if (NowPattern != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chk1"));
		//ColliderNotify();
	}
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Chk"));
}