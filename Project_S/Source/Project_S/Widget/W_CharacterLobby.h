// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_CharacterLobby.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_CharacterLobby : public UMainUserWidget
{
	GENERATED_BODY()
public:
	UW_CharacterLobby(const FObjectInitializer& ObjectInitializer);

	//void UpdateSlots(const TArray<FS_Slot>& Slots);
private:
	TSubclassOf<class UW_LobbySlot> UW_LobbyWidget;
	class UW_LobbySlot* W_LobbyWidget;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Char;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Start;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Del;

};
