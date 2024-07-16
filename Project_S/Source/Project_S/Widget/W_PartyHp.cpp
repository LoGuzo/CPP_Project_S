// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PartyHp.h"
#include "W_PartyHpSlot.h"

UW_PartyHp::UW_PartyHp(const FObjectInitializer& ObjectInitalizer) :Super(ObjectInitalizer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_PartyHpSlot.WBP_PartyHpSlot_C'"));
	if (UW.Succeeded())
	{
		TW_PartyHpSlot = UW.Class;
	}
}