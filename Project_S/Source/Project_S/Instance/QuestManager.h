// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Project_S/S_StructureAll.h"
#include "QuestManager.generated.h"

#define ZeroMemory(data){delete data; data = nullptr;}

USTRUCT(BlueprintType)
struct FQuestNode
{
	GENERATED_BODY()

	FQuestInfoData* QuestInfo;

	FQuestData* QuestData;

	int32 CurrentValue;

	FQuestNode* LeftChild;

	FQuestNode* RightChild;

	bool IsComplete() const
	{
		return CurrentValue >= QuestData->ClearValue;
	}
};
/**
 * 
 */
UCLASS()
class PROJECT_S_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
private:
	TMap<int32, TSharedPtr<FTableRowBase>> QuestInfoData;
	TMap<int32, TSharedPtr<FTableRowBase>> QuestRequiredData;

	TArray<FQuestNode*> NowQuest;
	FQuestNode* CreateQuestNode(int32 QuestID);

protected:
	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

public:
	void UpdateQuestProgress(FQuestNode* QuestNode, int32 MonsterID);

	TArray<FQuestNode*> GetNowQuest() { return NowQuest; }
};
