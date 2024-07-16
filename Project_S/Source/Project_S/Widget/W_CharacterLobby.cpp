// Fill out your copyright notice in the Description page of Project Settings.


#include "W_CharacterLobby.h"
#include "W_LobbySlot.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "Project_S/Actor/LobbyCharacter.h"
#include "Project_S/Controllers/LobbyController.h"
#include "Project_S/Controllers/MainPlayerController.h"
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
	Box_Char->ClearChildren();
	for (const FString& slot : Slots)
	{
		W_LobbyWidget = CreateWidget<UW_LobbySlot>(GetWorld(), UW_LobbyWidget);
		if (W_LobbyWidget)
		{
			W_LobbyWidget->SetCharName(slot);
			W_LobbyWidget->SetIndex(index);
			W_LobbyWidget->OnUpDateButton.AddUObject(this, &UW_CharacterLobby::SetClickButton);
		}
		Box_Char->AddChild(W_LobbyWidget);
		index++;
	}
}

void UW_CharacterLobby::NativeConstruct()
{
	Super::NativeConstruct();
	if (Btn_Start)
	{
		Btn_Start->SetIsEnabled(false);
		Btn_Start->OnClicked.AddDynamic(this, &UW_CharacterLobby::GameStart);
	}
	if (Btn_Del)
	{
		Btn_Del->SetIsEnabled(false);
		Btn_Del->OnClicked.AddDynamic(this, &UW_CharacterLobby::DelCharacter);
	}
}

void UW_CharacterLobby::NativePreConstruct()
{
	Super::NativePreConstruct();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (MyGameInstance->GetUserData())
		{
			HaveChar = MyGameInstance->GetUserData()->HaveChar;
			if (HaveChar.Num() != 0)
				UpdateSlots(HaveChar);
		}
	}
}

void UW_CharacterLobby::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_CharacterLobby::GameStart()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	APlayerState* UserState = GetOwningPlayer()->PlayerState;
	if (MyGameInstance)
	{
		MyGameInstance->SetUserName(HaveChar[MyGameInstance->GetIndex()]);
		MyGameInstance->NextLoadingLevel("DemoMap");
	}
}

void UW_CharacterLobby::DelCharacter()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (MyGameInstance->GetIndex() >= 0)
		{
			FUserID DelUserID = *MyGameInstance->GetUserData();
			MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->DelMyData(DelUserID.HaveChar[MyGameInstance->GetIndex()]);
			DelUserID.HaveChar[MyGameInstance->GetIndex()] = "";
			MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->SetMyData(DelUserID.ID, &DelUserID);
			UpdateSlots(DelUserID.HaveChar);
			MyGameInstance->SetUserData(DelUserID);
		}
	}
}

void UW_CharacterLobby::SetClickButton()
{
	if (Btn_Start)
		Btn_Start->SetIsEnabled(true);
	if (Btn_Del)
		Btn_Del->SetIsEnabled(true);
}


