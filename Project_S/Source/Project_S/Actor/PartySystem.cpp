// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySystem.h"
#include "Project_S/Character/UserCharacter.h"

UPartySystem::UPartySystem()
{
	MaxMemberCnt = 4;
}

void UPartySystem::AddUser(AUserCharacter* Member)
{
	if (Members.Num() < MaxMemberCnt && !Members.Contains(Member))
	{
		Members.Add(Member);

		if (Members.Num() == 1)
			SetLeader(Member);
	}
}

void UPartySystem::RemoveUser(AUserCharacter* Member)
{
	if (Members.Num() > 0 && Members.Contains(Member))
	{
		Members.Remove(Member);

		if (Leader == Member && Members.Num() > 0)
		{
			SetLeader(Members[0]);
		}
	}
}

void UPartySystem::SetLeader(AUserCharacter* _Leader)
{
	if (Members.Contains(_Leader))
	{
		Leader = _Leader;
	}
}
