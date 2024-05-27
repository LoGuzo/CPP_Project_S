// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginController.h"
#include "Project_S/Widget/W_Login.h"
#include "Kismet/GameplayStatics.h"

ALoginController::ALoginController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> LoginWidget(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Login.WBP_Login_C'"));
	if (LoginWidget.Class)
	{
		ULogin_Widget = LoginWidget.Class;
	}
}

void ALoginController::LoginSuccessful(const FString& Username)
{
	PlayerUsername = Username;

	// 다음 맵으로 전환
	UGameplayStatics::OpenLevel(this, FName("LobbyMap"));
}

void ALoginController::BeginPlay()
{
	Super::BeginPlay();

	if (ULogin_Widget)
	{
		W_Login = CreateWidget<UW_Login>(GetWorld(), ULogin_Widget);
		if (W_Login)
		{
			W_Login->AddToViewport();

			// 필요시 마우스 커서 표시
			bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(W_Login->TakeWidget());
			SetInputMode(InputMode);
		}
	}
}