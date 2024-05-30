// Fill out your copyright notice in the Description page of Project Settings.


#include "W_CharacterLobby.h"
#include "W_LobbySlot.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Actor/LobbyCharacter.h"
#include "Project_S/Instance/S_GameInstance.h"

UW_CharacterLobby::UW_CharacterLobby(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Type = E_Widget::E_HUD;
	static ConstructorHelpers::FClassFinder<UUserWidget>W_Lobby(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_LobbySlot.WBP_LobbySlot_C'"));
	if (W_Lobby.Succeeded())
	{
		UW_LobbyWidget = W_Lobby.Class;
	}
}

void UW_CharacterLobby::UpdateSlots(const TArray<FString>& Slots)
{
	int32 index = 0;
	for (const FString& slot : Slots)
	{
		W_LobbyWidget = CreateWidget<UW_LobbySlot>(GetWorld(), UW_LobbyWidget);
		if (W_LobbyWidget)
		{
			W_LobbyWidget->SetCharName(slot);
			W_LobbyWidget->SetIndex(index);
		}
		Box_Char->AddChild(W_LobbyWidget);
		index++;
	}
}

void UW_CharacterLobby::NativeConstruct()
{
	Super::NativeConstruct();
	if (Btn_Start)
		Btn_Start->OnClicked.AddDynamic(this, &UW_CharacterLobby::GameStart);
}

void UW_CharacterLobby::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (MyGameInstance->GetUserData())
		{
			UserData = StaticCastSharedPtr<FUserID>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->GetMyData(*MyGameInstance->GetUserData()->ID));
			if (UserData.IsValid())
			{
				HaveChar = UserData.Pin()->HaveChar;
				if (HaveChar.Num()!= 0)
					UpdateSlots(HaveChar);
			}
		}
	}
}

void UW_CharacterLobby::NativeDestruct()
{
	Super::NativeDestruct();
	if (UserData.IsValid())
		UserData.Reset();
}

void UW_CharacterLobby::GameStart()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		//MyGameInstance
	}
}


