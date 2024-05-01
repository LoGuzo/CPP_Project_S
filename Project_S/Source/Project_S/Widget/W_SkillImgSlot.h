// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Drag.h"
#include "DO_DragDrop.h"
#include "W_SkillImgSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_SkillImgSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UW_SkillImgSlot(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(VisibleAnywhere)
	FName SkillKey;

	TSubclassOf<class UW_Drag> U_DragImg;

	UW_Drag* DragImg;

	UDO_DragDrop* DO_Drag;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Skill;

public:
	FName GetSkillKey() { return SkillKey; }

	void SetSkillKey(FName _SkillKey);

};
