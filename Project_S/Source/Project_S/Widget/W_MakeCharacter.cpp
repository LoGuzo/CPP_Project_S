// Fill out your copyright notice in the Description page of Project Settings.


#include "W_MakeCharacter.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Project_S/S_StructureAll.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Actor/MakeCharacterPawn.h"
#include "Project_S/Controllers/MakeCharController.h"
#include "Project_S/Instance/S_GameInstance.h"

void UW_MakeCharacter::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (Btn_Warrior)
		Btn_Warrior->OnClicked.AddDynamic(this, &UW_MakeCharacter::SetWarrior);
	if (Btn_Mage)
		Btn_Mage->OnClicked.AddDynamic(this, &UW_MakeCharacter::SetMage);
	if (Btn_Healer)
		Btn_Healer->OnClicked.AddDynamic(this, &UW_MakeCharacter::SetHealer);
	if (Btn_Make)
		Btn_Make->OnClicked.AddDynamic(this, &UW_MakeCharacter::GoToMake);
	if (Btn_Back)
		Btn_Back->OnClicked.AddDynamic(this, &UW_MakeCharacter::GoToBack);
}

void UW_MakeCharacter::NativeConstruct()
{
	Super::NativeConstruct();
	NowPawn = Cast<AMakeCharacterPawn>(GetOwningPlayerPawn());
	bIsRotating = false;
}

void UW_MakeCharacter::SetWarrior()
{
	if (NowPawn)
	{
		NowPawn->SetMeshRotation();
		NowPawn->LoadData("Warrior");
	}
	NowCharClass = E_CharClass::E_Warrior;
}

void UW_MakeCharacter::SetMage()
{
	if (NowPawn)
	{
		NowPawn->SetMeshRotation();
		NowPawn->LoadData("Magician");
	}
	NowCharClass = E_CharClass::E_Magician;
}

void UW_MakeCharacter::SetHealer()
{
	if (NowPawn)
	{
		NowPawn->SetMeshRotation();
		NowPawn->LoadData("Healer");
	}
	NowCharClass = E_CharClass::E_Healer;
}

void UW_MakeCharacter::GoToMake()
{
	FString CharName = Text_CharacterName->GetText().ToString();
	if(CharName != "")
		ValidateID(CharName);
}
void UW_MakeCharacter::GoToBack()
{
	UE_LOG(LogTemp, Warning, TEXT("None"))
	AMakeCharController* PlayerController = Cast<AMakeCharController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
		PlayerController->LobbyLevel();
}

void UW_MakeCharacter::ValidateID(const FString& Username)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto UserData = StaticCastSharedPtr<FMyCharacterData>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->GetMyData(Username));
		if (UserData.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("No"))
		}
		else
		{
			FMyCharacterData NewCharacterData;
			NewCharacterData.CharID = Username;
			NewCharacterData.Type = NowCharClass;
			NewCharacterData.Level = 1;
			NewCharacterData.Exp = 0.f;
			MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->SetMyData(Username, &NewCharacterData);

			FUserID NewUserID = *MyGameInstance->GetUserData();
			NewUserID.HaveChar[MyGameInstance->GetIndex()] = Username;

			MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->SetMyData(NewUserID.ID, &NewUserID);

			GoToBack();
		}
	}
}

FReply UW_MakeCharacter::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsRotating = true;
		LastMousePosition = InMouseEvent.GetScreenSpacePosition();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply UW_MakeCharacter::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsRotating = false;
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply UW_MakeCharacter::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsRotating && NowPawn)
	{
		FVector2D CurrentMousePosition = InMouseEvent.GetScreenSpacePosition();
		FVector2D MouseDelta = CurrentMousePosition - LastMousePosition;

		RotateCharacter(MouseDelta.X);

		LastMousePosition = CurrentMousePosition;
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UW_MakeCharacter::RotateCharacter(float DeltaYaw)
{
	if (NowPawn)
	{
		FRotator NewRotation = NowPawn->GetMesh()->GetRelativeRotation();
		NewRotation.Yaw += DeltaYaw * -0.2f;
		NowPawn->GetMesh()->SetRelativeRotation(NewRotation);
	}
}
