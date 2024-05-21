// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_S/S_StructureAll.h"
#include "C_QuickSlotComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnQuickUpdated);

struct FTableRowBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API UC_QuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_QuickSlotComponent();

	FOnQuickUpdated OnQuickUpdated;
private:
	TArray<FS_Slot> SkillSlots;
	TArray<FS_Slot> PotionSlots;

	FS_Slot LocalSlot;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	TMap<int32, int32> BindTarget;

	TArray<FS_Slot> GetSkillSlots() { return SkillSlots; }
	TArray<FS_Slot> GetPotionSlots() { return PotionSlots; }
	FString GetSkillSlot(int32 _Index) { return SkillSlots[_Index].ItemName.ToString(); }
	FString GetPotionSlot(int32 _Index) { return PotionSlots[_Index].ItemName.ToString(); }
	void UsePotionSlot(int32 _Index) { PotionSlots[_Index].Amount -= 1; }
	void SetSkillSlots(const TArray<FS_Slot>& _Slots);
	void SetPotionSlots(const TArray<FS_Slot>& _Slots);

	void SkillToQuick(int32 _SkillIndex, int32 _TargetIndex, class UC_SkillComponent* _SkillCom);
	void InvenToQuick(int32 _InvenIndex, int32 _TargetIndex, class UC_InventoryComponent* _InvenCom);
		
};
