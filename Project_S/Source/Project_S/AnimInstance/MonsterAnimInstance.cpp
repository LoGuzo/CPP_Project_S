// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Project_S/Character/EnemyCharacter.h"

UMonsterAnimInstance::UMonsterAnimInstance() : NowPattern(nullptr), Monster(nullptr)
{
	Speed = 0.0f;
}

UMonsterAnimInstance::~UMonsterAnimInstance()
{
	if (NowPattern != nullptr)
	{
		NowPattern = nullptr;
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (::IsValid(Monster))
	{
		Speed = Monster->GetVelocity().Size();
	}
}

void UMonsterAnimInstance::PlaySome(TSharedPtr<FMonsterPattern>_Data)
{
	NowPattern = _Data.Get();
	if (NowPattern->AnimMontage != nullptr)
	{
		if (!Montage_IsPlaying(NowPattern->AnimMontage))
		{
			Montage_Play(NowPattern->AnimMontage, 1.f);
		}
	}
}

void UMonsterAnimInstance::ColliderNotify()
{
	switch (NowPattern->PatternType)
	{
	case E_SkillType::E_Melee:
		Monster->MeleeAttackCheck(NowPattern->Range);
		break;
	case E_SkillType::E_Scope:
		Monster->ScopeAttackCheck(NowPattern->Range);
		break;
	case E_SkillType::E_Shot:
		Monster->ShotAttackCheck();
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
	ColliderNotify();
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	if (Monster != nullptr)
	{
		Monster->IsAttacking = false;
		Monster->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	}
}

void UMonsterAnimInstance::AnimNotify_Died()
{
	if (Monster != nullptr)
	{
		Monster->DiedEnemy();
	}
}

void UMonsterAnimInstance::AnimNotify_AnyMove()
{
	if (Monster != nullptr)
	{
		Monster->AnyMove();
	}
}

void UMonsterAnimInstance::AnimNotify_Make_Projectile()
{
	if (Monster != nullptr)
	{
		Monster->Set_Projectile();
	}
}
