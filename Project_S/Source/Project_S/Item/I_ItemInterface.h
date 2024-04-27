// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_ItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_S_API II_ItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(class AUserCharacter* _UserCharacter) = 0;
};
