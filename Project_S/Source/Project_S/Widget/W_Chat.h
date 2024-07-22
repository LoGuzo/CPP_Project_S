// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_Chat.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Chat : public UMainUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void AddChatMessage(const FString& Message);
	void SetChatInputTextMessage(const FText& Text);

	TSharedPtr<class SWidget> GetChatInputTextObject();

private:
	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* Box_Scroll;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* Text_Chat;

	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
