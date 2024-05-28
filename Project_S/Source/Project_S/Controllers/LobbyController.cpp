// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Project_S/Widget/W_CharacterLobby.h"

ALobbyController::ALobbyController()
{
	bShowMouseCursor = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> LobbyWidget(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_CharacterLobby.WBP_CharacterLobby_C'"));
	if (LobbyWidget.Class)
	{
		ULobby_Widget = LobbyWidget.Class;
	}
}

void ALobbyController::BeginPlay()
{
	Super::BeginPlay();
	if (ULobby_Widget)
	{
		W_CharacterLobby = CreateWidget<UW_CharacterLobby>(GetWorld(), ULobby_Widget);
		if (W_CharacterLobby)
		{
			W_CharacterLobby->AddToViewport();

			FInputModeGameAndUI LobbyInputMode;
			LobbyInputMode.SetWidgetToFocus(W_CharacterLobby->TakeWidget());
			SetInputMode(LobbyInputMode);
		}
	}
}