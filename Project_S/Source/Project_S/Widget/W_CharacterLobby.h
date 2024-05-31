// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_CharacterLobby.generated.h"

/**
 * 
 */
struct FUserID;

UCLASS()
class PROJECT_S_API UW_CharacterLobby : public UMainUserWidget
{
	GENERATED_BODY()
public:
	UW_CharacterLobby(const FObjectInitializer& ObjectInitializer);

	void UpdateSlots(const TArray<FString>& Slots);

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

private:
	TSubclassOf<class UW_LobbySlot> UW_LobbyWidget;
	class UW_LobbySlot* W_LobbyWidget;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Box_Char;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Start;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Del;

	UFUNCTION()
	void GameStart();

	UFUNCTION()
	void DelCharacter();

	UFUNCTION()
	void SetClickButton();

	TArray<FString> HaveChar;
};
