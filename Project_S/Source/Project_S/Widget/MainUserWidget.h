// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_S/E_ItemType.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	E_Widget Type;
};
