// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_AddUser.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_AddUser : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void FindID();

	UFUNCTION(BlueprintCallable)
	void SignUp();

	UFUNCTION(BlueprintCallable)
	void Back();

protected:
	virtual void NativeConstruct() override;

	// 로그인 체크
	bool ValidateID(const FString& Username);

private:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Txt_ID;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Txt_Pass;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ChkID;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Add;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_X;

	UFUNCTION()
	void ValidateIDText(const FText& Text);

	UFUNCTION()
	void ValidatePWText(const FText& Text);
};
