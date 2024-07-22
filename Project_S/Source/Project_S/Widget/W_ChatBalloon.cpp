// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ChatBalloon.h"
#include "Components/TextBlock.h"

void UW_ChatBalloon::SetSpeechBubble(const FText& Message)
{
	if(Txt_Bubble)
		Txt_Bubble->SetText(Message);
}