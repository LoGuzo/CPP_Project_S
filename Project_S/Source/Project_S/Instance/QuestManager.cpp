// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Instance/S_GameInstance.h"

void UQuestManager::PostInitProperties()
{
	Super::PostInitProperties();

	auto MyInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyInstance)
	{
		QuestInfoData = MyInstance->MyDataManager.FindRef(E_DataType::E_QuestInfo)->GetDataMap();
		QuestRequiredData = MyInstance->MyDataManager.FindRef(E_DataType::E_QuestData)->GetDataMap();
		NowQuest.Add(CreateQuestNode(1111111));
	}
}

void UQuestManager::BeginDestroy()
{
	Super::BeginDestroy();

	if (NowQuest.Num() > 0)
	{
		for (auto Data : NowQuest)
			ZeroMemory(Data);
	}
}

FQuestNode* UQuestManager::CreateQuestNode(int32 QuestID)
{
	FQuestNode* NewNode = new FQuestNode();

	NewNode->QuestInfo = static_cast<FQuestInfoData*>(QuestInfoData.FindRef(QuestID).Get());
	NewNode->QuestData = static_cast<FQuestData*>(QuestRequiredData.FindRef(NewNode->QuestInfo->QuestID).Get());
	NewNode->CurrentValue = 0;

	if (NewNode->QuestInfo->SubQuestID.Num() == 1)
		NewNode->LeftChild = CreateQuestNode(NewNode->QuestInfo->SubQuestID[0]);
	else if (NewNode->QuestInfo->SubQuestID.Num() == 2)
	{
		NewNode->LeftChild = CreateQuestNode(NewNode->QuestInfo->SubQuestID[0]);
		NewNode->RightChild = CreateQuestNode(NewNode->QuestInfo->SubQuestID[1]);
	}

	return NewNode;
}

void UQuestManager::UpdateQuestProgress(int32 MonsterID)
{
	TArray<FQuestNode*> ToAdd;
	TArray<FQuestNode*> ToRemove;

	for (FQuestNode* QuestNode : NowQuest)
	{
		if (QuestNode && QuestNode->QuestData->MonsterID == MonsterID)
		{
			QuestNode->CurrentValue++;
			if (QuestNode->IsComplete())
			{
				ToRemove.Add(QuestNode);

				if (QuestNode->LeftChild)
					ToAdd.Add(QuestNode->LeftChild);
				if (QuestNode->RightChild)
					ToAdd.Add(QuestNode->RightChild);
			}
		}
	}

	for (FQuestNode* Node : ToRemove)
	{
		NowQuest.Remove(Node);
		ZeroMemory(Node);
	}

	NowQuest.Append(ToAdd);
}

void UQuestManager::AddFirstData()
{
	NowQuest.Add(CreateQuestNode(1111111));
}