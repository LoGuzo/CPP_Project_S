// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Actor/UserPlayerState.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Controllers/LoadingController.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Widget/MainUserWidget.h"

ALoadingGameMode::ALoadingGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> LoadScene(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Loading.WBP_Loading_C'"));
	if (LoadScene.Class)
	{
		W_LoadingScene = LoadScene.Class;
	}
	PlayerControllerClass = ALoadingController::StaticClass();
}

void ALoadingGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (W_LoadingScene)
	{
		LoadingScene = CreateWidget<UMainUserWidget>(GetWorld(), W_LoadingScene);
		if (LoadingScene)
		{
			LoadingScene->AddToViewport();
			NextLevel();
		}
	}
}


void ALoadingGameMode::NextLevel()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		// FLatentActionInfo 설정
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;  // 콜백을 받을 객체
		LatentInfo.ExecutionFunction = FName("OnLevelLoaded");  // 콜백 함수 이름
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = __LINE__;
		UGameplayStatics::LoadStreamLevel(this, FName(*MyGameInstance->GetNextLevelName()), true, false, LatentInfo);
	}
}

void ALoadingGameMode::OnLevelLoaded()
{
	/*auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		MyGameInstance->NextLevel(MyGameInstance->GetNextLevelName());
	}*/
	APlayerController* UserPlayerController = GetWorld()->GetFirstPlayerController();
	if (UserPlayerController)
	{
		UserPlayerController->ClientTravel(TEXT("127.0.0.1"), ETravelType::TRAVEL_Absolute, true);
	}
}