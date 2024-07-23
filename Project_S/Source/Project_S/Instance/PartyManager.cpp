// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyManager.h"
#include "Project_S/Actor/PartySystem.h"

UPartySystem* UPartyManager::CreateParty(AUserCharacter* Member)
{
	UPartySystem* NewParty = NewObject<UPartySystem>();
	NewParty->AddUser(Member);
	Parties.Add(NewParty);

	return NewParty;
}

void UPartyManager::AddMemberToParty(UPartySystem* Party, AUserCharacter* NewMember)
{
	if (Party)
		Party->AddUser(NewMember);
}

void UPartyManager::RemoveMemberFromParty(UPartySystem* Party, AUserCharacter* Member)
{
	if (Party)
		Party->RemoveUser(Member);
}

void UPartyManager::DisbandParty(UPartySystem* Party)
{
	if (Party)
	{
		Parties.Remove(Party);
		Party->ConditionalBeginDestroy();
	}
}
