// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Drag.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_Drag : public UUserWidget
{
	GENERATED_BODY()
private:
	FName ItemKey;
public:
	virtual void NativePreConstruct() override;

	void SetItemKey(FName _ItemKey);

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Drag;
};
