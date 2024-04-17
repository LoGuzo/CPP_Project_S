// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryMenu(const FObjectInitializer& ObjectInitializer);
	class UUserWidget* WBP_Inventory;
};
