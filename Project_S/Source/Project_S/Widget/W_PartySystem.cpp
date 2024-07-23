// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PartySystem.h"

UW_PartySystem::UW_PartySystem(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_PartySlot.WBP_PartySlot_C'"));
	if (UW.Succeeded())
	{
		TW_PartySlot = UW.Class;
	}
}