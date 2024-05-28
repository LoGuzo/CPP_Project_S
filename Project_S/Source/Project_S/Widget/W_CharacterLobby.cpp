// Fill out your copyright notice in the Description page of Project Settings.


#include "W_CharacterLobby.h"
#include "W_LobbySlot.h"

UW_CharacterLobby::UW_CharacterLobby(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_LobbySlot>W_Lobby(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_LobbySlot.WBP_LobbySlot_C'"));
	if (W_Lobby.Succeeded())
	{
		UW_LobbyWidget = W_Lobby.Class;
	}
}
