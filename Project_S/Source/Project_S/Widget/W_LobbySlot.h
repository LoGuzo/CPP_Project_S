// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_LobbySlot.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnUpDateButton);
/**
 * 
 */
struct FMyCharacterData;

UCLASS()
class PROJECT_S_API UW_LobbySlot : public UMainUserWidget
{
	GENERATED_BODY()

public:
	UW_LobbySlot(const FObjectInitializer& ObjectInitializer);

	void SetCharName(FString _CharName);
	void SetIndex(int32 _SlotIndex);
	void SetCharacterImage(UTextureRenderTarget2D* RenderTarget);

	FOnUpDateButton OnUpDateButton;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void GoToCreate();
	
	UFUNCTION()
	void SetInstanceIndex();

	void SetWidget();

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Char;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Char;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Create;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Box_Info;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Lvl;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Class;

	int32 SlotIndex;

	FString CharName;

	TWeakPtr<FMyCharacterData> UserData;

	class ALobbyCharacter* LobbyCharacter;

	UMaterialInterface* RenderTargetMaterial;

	class MappingClass* CharacterTypeMapping;
};
