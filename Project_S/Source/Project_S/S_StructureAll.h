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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AA_Item> ItemClass;
};

USTRUCT()
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxExp;

};

USTRUCT()
struct FS_Slot : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemConName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AA_Item> ItemClass;
};

USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot> MyEquip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot> MyInventory;
};

USTRUCT()
struct FSkillTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_SkillType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Req_Lvl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cur_Lvl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Max_Lvl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill_Img;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Skill_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Skill_Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCurveBase* AnimCurve;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class Skill> SkillClass;*/
};


USTRUCT()
struct FResult : public FTableRowBase 
{
	GENERATED_BODY()

	int Index;
	bool IsFindItem;
};

