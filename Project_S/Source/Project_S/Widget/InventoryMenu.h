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

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativePreConstruct() override;

	TSubclassOf<class UW_Inventory> TWBP_Inventory;

	UPROPERTY(meta = (BindWidget))
	class UW_Inventory* WBP_Inventory;
};
