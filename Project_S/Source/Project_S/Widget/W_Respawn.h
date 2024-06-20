// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_Respawn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Respawn : public UMainUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetUser(class AUserCharacter* _UserCharacter);

	UFUNCTION()
	void Respawn();
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Respawn;

	class AUserCharacter* UserCharacter;
};
