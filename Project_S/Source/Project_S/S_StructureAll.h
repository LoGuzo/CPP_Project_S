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
	int32 ID;

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
	float DropChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AA_Item> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStreamableRenderAsset> ItemMesh;
};

USTRUCT()
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_CharClass Type;

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
	E_ItemType ItemConName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AA_Item> ItemClass;
};

USTRUCT()
struct FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_MonsterType Type;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DropItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot> MonsterSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> MonsterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UMaterialInterface> MonsterMaterial;
};

USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_CharClass Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot> MyEquip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot> MyInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot>	MySkillQuick;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Slot>	MyPotionQuick;
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
struct FMonsterPattern : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_SkillType PatternType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Skill_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* AnimMontage;
};

USTRUCT()
struct FSpawnMonsterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MonsterName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_MonsterType MonsterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MonsterScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> PatrolLocation;
};

USTRUCT()
struct FSpawnData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Spanwer Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnerScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpawnMonsterData> SpawnMonster;
};

USTRUCT()
struct FUserID: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> HaveChar;
};

USTRUCT()
struct FCharacterClass : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_CharClass Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Img_Class;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> ClassMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UAnimInstance> ClassAnim;
};

USTRUCT()
struct FResult : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFindItem;
};

