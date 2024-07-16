// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartySystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UPartySystem : public UObject
{
	GENERATED_BODY()
	
private:
	UPartySystem();

	TArray<class AUserCharacter*> Members;
	
	class AUserCharacter* Leader;

	int32 MaxMemberCnt;

public:
	void AddUser(class AUserCharacter* Member);
	void RemoveUser(class AUserCharacter* Member);
	void SetLeader(class AUserCharacter* _Leader);
};
