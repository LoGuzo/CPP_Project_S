// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "E_ItemType.h"
#include "S_StructureAll.generated.h"
/**
 * 
 */
USTRUCT()
struct FS_Item : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_ItemType ItemType;
};

USTRUCT()
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExp;

};

USTRUCT()
struct FS_Slot : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
};

USTRUCT()
struct FResult : public FTableRowBase {

	GENERATED_BODY()
	int Index;
	bool IsFindItem;
};

