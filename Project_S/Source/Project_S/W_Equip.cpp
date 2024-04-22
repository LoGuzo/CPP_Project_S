// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Equip.h"
#include "W_Slot.h"
#include "UserCharacter.h"
#include "C_EqiupComponent.h"
#include "Kismet/GameplayStatics.h"

UW_Equip::UW_Equip(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_Slot>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_Slot.WBP_Slot_C'"));
	if (UW.Succeeded())
	{
		USlot_Weapon = UW.Class;
		USlot_Head = UW.Class;
		USlot_Shoes = UW.Class;
		USlot_Armor = UW.Class;
		USlot_Cape = UW.Class;
	}
}

void UW_Equip::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(true);
	}
}

void UW_Equip::NativeDestruct()
{
	Super::NativeDestruct();
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {

		FInputModeGameOnly InputMode;
		playerController->SetInputMode(InputMode);
		playerController->SetShowMouseCursor(false);
	}
}

void UW_Equip::NativePreConstruct()
{
	Super::NativePreConstruct();

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter)
	{
		equipCom = playerCharacter->FindComponentByClass<UC_EqiupComponent>();
		if (equipCom)
		{
			ShowEquip(equipCom);
		}
	}
}

void UW_Equip::ShowEquip(UC_EqiupComponent* _EquipCom)
{
	UpdateEquip(_EquipCom->GetSlots());
}

void UW_Equip::UpdateEquip(const TArray<FS_Slot>& _Slots)
{
	int32 index = 0;
	for (const FS_Slot& slot : _Slots)
	{
		switch (index)
		{
		case 0:
			Wrap_Weapon->ClearChildren();
			Slot_Weapon = CreateWidget<UW_Slot>(GetWorld(), USlot_Weapon);
			if (Slot_Weapon)
			{
				Slot_Weapon->SetItemKey(slot.ItemName);
				Slot_Weapon->SetAmount(slot.Amount);
				Slot_Weapon->SetEquipCom(equipCom);
				Slot_Weapon->SetConName(EquipMap.FindRef(index));
				Slot_Weapon->SetConIndex(0);
			}
			Wrap_Weapon->AddChild(Slot_Weapon);
			break;
		case 1:
			Wrap_Head->ClearChildren();
			Slot_Head = CreateWidget<UW_Slot>(GetWorld(), USlot_Weapon);
			if (Slot_Head)
			{
				Slot_Head->SetItemKey(slot.ItemName);
				Slot_Head->SetAmount(slot.Amount);
				Slot_Head->SetEquipCom(equipCom);
				Slot_Head->SetConName(EquipMap.FindRef(index));
				Slot_Head->SetConIndex(0);
			}
			Wrap_Head->AddChild(Slot_Head);
			break;
		case 2:
			Wrap_Shoes->ClearChildren();
			Slot_Shoes = CreateWidget<UW_Slot>(GetWorld(), USlot_Weapon);
			if (Slot_Shoes)
			{
				Slot_Shoes->SetItemKey(slot.ItemName);
				Slot_Shoes->SetAmount(slot.Amount);
				Slot_Shoes->SetEquipCom(equipCom);
				Slot_Shoes->SetConName(EquipMap.FindRef(index));
				Slot_Shoes->SetConIndex(0);
			}
			Wrap_Shoes->AddChild(Slot_Shoes);
			break;
		case 3:
			Wrap_Armor->ClearChildren();
			Slot_Armor = CreateWidget<UW_Slot>(GetWorld(), USlot_Weapon);
			if (Slot_Armor)
			{
				Slot_Armor->SetItemKey(slot.ItemName);
				Slot_Armor->SetAmount(slot.Amount);
				Slot_Armor->SetEquipCom(equipCom);
				Slot_Armor->SetConName(EquipMap.FindRef(index));
				Slot_Armor->SetConIndex(0);
			}
			Wrap_Armor->AddChild(Slot_Armor);
			break;
		case 4:
			Wrap_Cape->ClearChildren();
			Slot_Cape = CreateWidget<UW_Slot>(GetWorld(), USlot_Weapon);
			if (Slot_Cape)
			{
				Slot_Cape->SetItemKey(slot.ItemName);
				Slot_Cape->SetAmount(slot.Amount);
				Slot_Cape->SetEquipCom(equipCom);
				Slot_Cape->SetConName(EquipMap.FindRef(index));
				Slot_Cape->SetConIndex(0);
			}
			Wrap_Cape->AddChild(Slot_Cape);
			break;
		default:
			break;
		}
		index++;
	}
}