// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Chat.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Controllers/MainPlayerController.h"

void UW_Chat::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Chat->OnTextCommitted.AddDynamic(this, &UW_Chat::OnChatTextCommitted);
}

void UW_Chat::AddChatMessage(const FString& Message)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(Box_Scroll);
	NewTextBlock->SetText(FText::FromString(Message));

	Box_Scroll->AddChild(NewTextBlock);
	Box_Scroll->ScrollToEnd();
}

void UW_Chat::SetChatInputTextMessage(const FText& Text)
{
	Text_Chat->SetText(Text);
}

TSharedPtr<SWidget> UW_Chat::GetChatInputTextObject()
{
	return Text_Chat->GetCachedWidget();
}

void UW_Chat::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MyPC == nullptr) return;

	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		if (Text.IsEmpty() == false)
		{
			MyPC->SendMessage(Text); // 메시지 보냄.
			SetChatInputTextMessage(FText::GetEmpty()); // 메세지 전송했으니, 비워줌.
		}
		MyPC->FocusGame(); // 다시 게임으로 포커싱.
		break;
	case ETextCommit::OnCleared:
		MyPC->FocusGame(); // 다시 게임으로 포커싱.
		break;
	}
}