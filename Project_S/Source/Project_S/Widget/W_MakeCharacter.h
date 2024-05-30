// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_MakeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_MakeCharacter : public UMainUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void SetWarrior();
	UFUNCTION()
	void SetMage();
	UFUNCTION()
	void SetHealer();
	UFUNCTION()
	void GoToMake();
	UFUNCTION()
	void GoToBack();

	void ValidateID(const FString& Username);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
private:
	bool bIsRotating;

	FVector2D LastMousePosition;

	void RotateCharacter(float DeltaYaw);

	E_CharClass NowCharClass;

	class AMakeCharacterPawn* NowPawn;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Warrior;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Mage;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Healer;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Make;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Text_CharacterName;
};
