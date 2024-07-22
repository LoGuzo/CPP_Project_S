// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Widget/S_CharacterWidget.h"
#include "Project_S/Character/UserCharacter.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMainPlayerController::FocusChatInputText);
}

void AMainPlayerController::SendMessage(const FText& Text)
{
	AUserCharacter* UserCharacter = Cast<AUserCharacter>(GetPawn());
	if (UserCharacter)
	{
		FString UserName = UserCharacter->GetCharID();
		FString Message = FString::Printf(TEXT("%s : %s"), *UserName, *Text.ToString());

		Server_SendMessage(Message);
	}
}

void AMainPlayerController::FocusChatInputText()
{
	AUserCharacter* UserCharacter = Cast<AUserCharacter>(GetPawn());
	if (UserCharacter)
	{
		US_CharacterWidget* CharacterWidget = UserCharacter->GetHUDWidget();
		if (CharacterWidget)
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(CharacterWidget->GetChatInputTextObject());

			SetInputMode(InputMode);
		}
	}
}

void AMainPlayerController::FocusGame()
{
	SetInputMode(FInputModeGameOnly());
}

void AMainPlayerController::Server_SendMessage_Implementation(const FString& Message)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMainPlayerController* UserPlayerController = Cast<AMainPlayerController>(OutActor);
		if (UserPlayerController)
		{
			UserPlayerController->Client_SendMessage(Message);
		}
	}
}

void AMainPlayerController::Client_SendMessage_Implementation(const FString& Message)
{
	AUserCharacter* UserCharacter = Cast<AUserCharacter>(GetPawn());
	if (UserCharacter)
	{
		US_CharacterWidget* CharacterWidget = UserCharacter->GetHUDWidget();
		if (CharacterWidget)
		{
			CharacterWidget->AddChatMessage(Message);
		}
	}
}