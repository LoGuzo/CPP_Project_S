// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Drag.generated.h"

/**
 * 
 */
struct FS_Item;
struct FSkillTable;

UCLASS()
class PROJECT_S_API UW_Drag : public UUserWidget
{
	GENERATED_BODY()
private:
	FName ItemKey;
	FName SkillKey;
	TWeakPtr<FS_Item> ItemData;
	TWeakPtr<FSkillTable> SkillData;
public:
	virtual void NativePreConstruct() override;

	void SetItemKey(FName _ItemKey);
	void SetSkillKey(FName _SkillKey);

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Drag;
};
