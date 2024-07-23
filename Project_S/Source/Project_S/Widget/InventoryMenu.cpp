// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenu.h"
#include "W_Inventory.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/C_InventoryComponent.h"
#include <Kismet/GameplayStatics.h>


void UInventoryMenu::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(WBP_Inventory -> TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(true);
	}
}

void UInventoryMenu::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameOnly InputMode;
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(false);
	}
}

void UInventoryMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter)
	{
		UC_InventoryComponent* inventoryComponent = playerCharacter->FindComponentByClass<UC_InventoryComponent>();
		if (inventoryComponent)
			WBP_Inventory->ShowInventory(inventoryComponent);
	}
}