// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_S/S_StructureAll.h"
#include "C_SkillComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_S_API UC_SkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_SkillComponent();
		
private:
	TArray<FS_Slot> Slots;

	FS_Slot LocalSlot;

	int32 SkillCnt = 2;
protected:
	virtual void BeginPlay() override;

public:
	TArray<FS_Slot> GetSlots() { return Slots; }

	FS_Slot GetSlot(int32 _Index) { return Slots[_Index]; }

	void SetSlots(const TArray<FS_Slot>& _Slots);

	void SetSlot(int32 _Index, int32 _SkillPoint);
};
