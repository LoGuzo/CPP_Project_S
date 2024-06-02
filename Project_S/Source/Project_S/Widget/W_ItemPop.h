// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_ItemPop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_ItemPop : public UMainUserWidget
{
	GENERATED_BODY()

public:
	void SetInvenCom(class UC_InventoryComponent* _InvenCom);

	void SetTargetIndex(const int32 _TargetIndex);

	virtual void NativePreConstruct() override;
private:

	int32 TargetIndex;

	class UC_InventoryComponent* InvenCom;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ItemDrop;

	UFUNCTION()
	void ItemDrop();
};
