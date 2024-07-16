// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UPartyManager : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<class UPartySystem*> Parties;

	class UPartySystem* CreateParty(class AUserCharacter* Member);

	void AddMemberToParty(class UPartySystem* Party, class AUserCharacter* NewMember);

	void RemoveMemberFromParty(class UPartySystem* Party, class AUserCharacter* Member);

	void DisbandParty(class UPartySystem* Party);
};
