// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemAIController.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Project_S/Character/FirstCharacter.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/C_SkillComponent.h"
#include "Project_S/Character/EnemyCharacter.h"

void AGolemAIController::OnUnPossess()
{
	Super::OnUnPossess();
	for(int i = 0; i < SkillCooldownHandles.Num(); i++)
	{
		GetWorldTimerManager().ClearTimer(SkillCooldownHandles[i]);
	}
}


void AGolemAIController::AISerach()
{
	const auto Enemy = Cast<AFirstCharacter>(GetPawn());
	if (Enemy)
	{
		SkillCooldownHandles.SetNum(Enemy->GetSkillCom()->GetSlots().Num());
		CoolTime.SetNum(Enemy->GetSkillCom()->GetSlots().Num());
		for (int i = 0; i < Enemy->GetSkillCom()->GetSlots().Num(); i++)
		{
			CoolTime[i] = Enemy->GetSkillCom()->GetSlot(i).Amount;
		}
	}
	for (TActorIterator<AUserCharacter> It(GetWorld()); It; ++It)
	{
		AUserCharacter* SaveUser = *It;
		SearchChacter.Add(SaveUser);
	}
	SetRandomCharacter();
}

void AGolemAIController::Attack()
{
	const auto Enemy = Cast<AFirstCharacter>(GetPawn());
	if (Enemy->IsAttacking || IsMoving)
		return;
	if (User->GetIsDead())
	{
		SetRandomCharacter();
	}
	if (User && !IsDead)
	{
		int32 RandomPattern = RandRange(1, 3);
		if (SDistance(User->GetActorLocation(), GetPawn()->GetActorLocation()) <= 400.f * GetPawn()->GetActorScale3D().X)
		{
			LookAtPlayer();
			Enemy->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Dash"));
			switch (RandomPattern)
			{
			case 1:
			{
				if (!IsSkillOnCooldown(0)) {
					if(Enemy)
					{
						Enemy->UseSkill(Enemy->GetSkillCom()->GetSlot(0).ItemName.ToString());
						Enemy->IsAttacking = true;
						GetWorld()->GetTimerManager().SetTimer(SkillCooldownHandles[0], FTimerDelegate::CreateUObject(this, &AGolemAIController::OnSkillCooldownComplete, 0), Enemy->GetSkillCom()->GetSlot(0).Amount, false);
					}
				}
			}
			break;
			case 2:
			{
				if (!IsSkillOnCooldown(3)) {
					if (Enemy) {
						Enemy->UseSkill(Enemy->GetSkillCom()->GetSlot(3).ItemName.ToString());
						Enemy->IsAttacking = true;
						GetWorld()->GetTimerManager().SetTimer(SkillCooldownHandles[3], FTimerDelegate::CreateUObject(this, &AGolemAIController::OnSkillCooldownComplete, 3), Enemy->GetSkillCom()->GetSlot(3).Amount, false);
					}
				}
			}
			break;
			case 3:
			{
				if (!IsSkillOnCooldown(4)) {
					if (Enemy) {
						Enemy->UseSkill(Enemy->GetSkillCom()->GetSlot(4).ItemName.ToString());
						Enemy->IsAttacking = true;
						GetWorld()->GetTimerManager().SetTimer(SkillCooldownHandles[4], FTimerDelegate::CreateUObject(this, &AGolemAIController::OnSkillCooldownComplete, 4), Enemy->GetSkillCom()->GetSlot(4).Amount, false);
					}
				}
			}
			break;
			default:
				break;
			}
		}
	}
	IsMoving = false;
	ChkState = E_State::E_Move;
}

void AGolemAIController::SetRandomCharacter()
{
	if (!SearchChacter.IsValidIndex(0))
		return;
	int32 RandomPattern = RandRange(0, SearchChacter.Num()-1);
	User = SearchChacter[RandomPattern];
	auto Boss = Cast<AEnemyCharacter>(GetPawn());
	if (Boss)
	{
		if (Boss->GetIsDead())
			return;
		if (!User->GetIsDead())
		{
			Boss->SetTarget(User);
			ChkState = E_State::E_Move;
			GetWorldTimerManager().SetTimer(SearchHandle, this, &AGolemAIController::SetRandomCharacter, 10.f, true);
		}
		else
		{
			Boss->SetTarget(nullptr);
			ChkState = E_State::E_None;
			GetWorldTimerManager().SetTimer(SearchHandle, this, &AGolemAIController::SetRandomCharacter, 1.f, true);
		}
	}
}

void AGolemAIController::AIMove()
{
	const auto Enemy = Cast<AFirstCharacter>(GetPawn());
	if (IsMoving || Enemy->IsAttacking)
		return;
	IsMoving = true;
	IsMoveAtFirst = true;
	MoveToActor(User, 300.f * GetPawn()->GetActorScale3D().X);
	ChkState = E_State::E_Attack;
}

void AGolemAIController::OnSkillCooldownComplete(int32 SkillIndex)
{
	if (SkillCooldownHandles.IsValidIndex(SkillIndex))
	{
		SkillCooldownHandles[SkillIndex].Invalidate();
	}
}

bool AGolemAIController::IsSkillOnCooldown(int32 SkillIndex) const
{
	if (SkillCooldownHandles.IsValidIndex(SkillIndex))
	{
		return SkillCooldownHandles[SkillIndex].IsValid();
	}
	return false;
}