// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Respawn.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Character/UserCharacter.h"

void UW_Respawn::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Respawn)
		Btn_Respawn->OnClicked.AddDynamic(this, &UW_Respawn::Respawn);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(true);
	}
}
void UW_Respawn::NativeDestruct()
{
	Super::NativeDestruct();

	if (Btn_Respawn)
		Btn_Respawn->OnClicked.RemoveDynamic(this, &UW_Respawn::Respawn);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameOnly InputMode;
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(false);
	}
}

void UW_Respawn::SetUser(AUserCharacter* _UserCharacter)
{
	UserCharacter = _UserCharacter;
}

void UW_Respawn::Respawn()
{
	if (UserCharacter)
		UserCharacter->UserReset();
}
