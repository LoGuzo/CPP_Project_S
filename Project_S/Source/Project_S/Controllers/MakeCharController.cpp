// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeCharController.h"
#include "Components/Button.h"
#include "Misc/OutputDeviceNull.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableTextBox.h"
#include "Project_S/Widget/W_MakeCharacter.h"

AMakeCharController::AMakeCharController()
{
	bShowMouseCursor = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> MakeWidget(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_MakeChar.WBP_MakeChar_C'"));
	if (MakeWidget.Class)
	{
		UW_MakeCharWidget = MakeWidget.Class;
	}
}

void AMakeCharController::BeginPlay()
{
	Super::BeginPlay();
	BPFunction();
	if (UW_MakeCharWidget)
	{
		W_MakeCharacter = CreateWidget<UW_MakeCharacter>(GetWorld(), UW_MakeCharWidget);
		if (W_MakeCharacter)
		{
			W_MakeCharacter->AddToViewport();

			FInputModeUIOnly LobbyInputMode;
			LobbyInputMode.SetWidgetToFocus(W_MakeCharacter->TakeWidget());
			SetInputMode(LobbyInputMode);
		}
	}
}
void AMakeCharController::BPFunction()
{
	FString str = "FadeFunc";
	FOutputDeviceNull ar;
	CallFunctionByNameWithArguments(*str, ar, nullptr, true);
}

void AMakeCharController::LobbyLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "LobbyMap");
}