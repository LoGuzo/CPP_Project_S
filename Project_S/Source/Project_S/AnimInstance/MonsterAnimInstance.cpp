// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Project_S/Character/EnemyCharacter.h"

UMonsterAnimInstance::UMonsterAnimInstance() : NowSkill(nullptr), Monster(nullptr)
{
	Speed = 0.0f;
}

UMonsterAnimInstance::~UMonsterAnimInstance()
{
	if (NowSkill.IsValid())
	{
		NowSkill.Reset();
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (::IsValid(Monster))
	{
		Speed = Monster->GetVelocity().Size();
	}
	if (NowSkill != nullptr)
	{
		if (Montage_IsPlaying(NowSkill.Pin()->AnimMontage))
		{
			int32 size = NotifyQueue.AnimNotifies.Num();
			if (size <= 0) return;
			for (int32 i = 0; i < size; i++)
			{
				FName name = NotifyQueue.AnimNotifies[i].GetNotify()->NotifyName;
				if (name == TEXT("Collider"))
				{
					if (Monster != nullptr)
					{
						ColliderNotify();
					}
				}
			}
		}
		else
			NowSkill = nullptr;
	}
}

void UMonsterAnimInstance::PlaySome(TWeakPtr<FSkillTable>_Data)
{
	NowSkill = _Data;
	if (NowSkill.Pin()->AnimMontage != nullptr)
	{
		if (!Montage_IsPlaying(NowSkill.Pin()->AnimMontage))
		{
			Montage_Play(NowSkill.Pin()->AnimMontage);
		}
	}
}

void UMonsterAnimInstance::ColliderNotify()
{
	switch (NowSkill.Pin()->Type)
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

void UMonsterAnimInstance::SetSpeed(const float _Speed)
{
	Speed = _Speed;
}

void UMonsterAnimInstance::SetMonster(AEnemyCharacter* _Monster)
{
	Monster = _Monster;
}