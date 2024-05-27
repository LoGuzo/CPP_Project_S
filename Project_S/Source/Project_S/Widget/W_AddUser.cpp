// Fill out your copyright notice in the Description page of Project Settings.


#include "W_AddUser.h"
#include "Components/Button.h"
#include "Project_S/S_StructureAll.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"


void UW_AddUser::NativeConstruct()
{
    if (Btn_ChkID)
        Btn_ChkID->OnClicked.AddDynamic(this, &UW_AddUser::FindID);
    if (Btn_Add)
        Btn_Add->OnClicked.AddDynamic(this, &UW_AddUser::SignUp);
    if (Btn_X)
        Btn_X->OnClicked.AddDynamic(this, &UW_AddUser::Back);
}

bool UW_AddUser::ValidateID(const FString& Username)
{
    auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (MyGameInstance)
    {
        auto UserData = StaticCastSharedPtr<FUserID>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->GetMyData(Username));
        if(UserData.IsValid())
            return UserData != nullptr;
    }
    return false;
}

void UW_AddUser::FindID()
{
    FString Username = Txt_ID->GetText().ToString();
    if (Username != "")
    {
        if (!ValidateID(Username))
        {
            UE_LOG(LogTemp, Warning, TEXT("OK"));
        }
        else
        {
            Txt_ID->SetText(FText::FromString(TEXT("")));
        }
    }
}

void UW_AddUser::SignUp()
{
    FUserID NowUserIDData;
    FString Username = Txt_ID->GetText().ToString();
    FString Password = Txt_Pass->GetText().ToString();
    NowUserIDData.ID = Username;
    NowUserIDData.Password = Password;

    if (Username != "" && Password != "")
    {
        auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
        if (MyGameInstance)
        {
            MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->SetMyData(Username, &NowUserIDData);
        }
    }
}

void UW_AddUser::Back()
{
    RemoveFromViewport();
}