// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Login.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Login : public UUserWidget
{
	GENERATED_BODY()

public:
	UW_Login(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void OnLogin();

	UFUNCTION(BlueprintCallable)
	void OnAddUser();

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	TSubclassOf<class UW_AddUser> UAddUser_Widget;
	class UW_AddUser* W_AddUser;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Text_ID;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Text_Pass;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Login;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_AddUser;

	// 로그인 체크
	void ValidateLogin(const FString& Username, const FString& Password);

	// Enter 바인딩
	UFUNCTION()
	void IDCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
