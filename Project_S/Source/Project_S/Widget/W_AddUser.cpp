// Fill out your copyright notice in the Description page of Project Settings.


#include "W_AddUser.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/S_StructureAll.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Components/EditableTextBox.h"


void UW_AddUser::NativeConstruct()
{
    Super::NativeConstruct();
    if (Btn_ChkID)
        Btn_ChkID->OnClicked.AddDynamic(this, &UW_AddUser::FindID);
    if (Btn_Add)
        Btn_Add->OnClicked.AddDynamic(this, &UW_AddUser::SignUp);
    if (Btn_X)
        Btn_X->OnClicked.AddDynamic(this, &UW_AddUser::Back);
    if (Txt_ID)
    {
        Txt_ID->OnTextChanged.Clear();
        Txt_ID->OnTextChanged.AddDynamic(this, &UW_AddUser::ValidateIDText);
    }
    if (Txt_Pass)
    {
        Txt_Pass->OnTextChanged.Clear();
        Txt_Pass->OnTextChanged.AddDynamic(this, &UW_AddUser::ValidatePWText);
    }
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
    NowUserIDData.HaveChar.SetNum(4);

    if (Username != "" && Password != "")
    {
        auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
        if (MyGameInstance)
        {
            MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->SetMyData(Username, &NowUserIDData);
        }
    }
    Back();
}

void UW_AddUser::Back()
{
    RemoveFromViewport();
}

void UW_AddUser::ValidateIDText(const FText& Text)
{
    FString str = Text.ToString();

    const FRegexPattern pattern = FRegexPattern(FString(TEXT("^[A-Za-z0-9]+$")));

    FRegexMatcher matcher(pattern, str);

    bool bMatch = matcher.FindNext();

    if (!bMatch)
        Txt_ID->SetText(FText::FromString(str.Left(str.Len() - 1)));
    else
    {
        if (str.Len() > 32)
        {
            str = str.Left(32);
            Txt_ID->SetText(FText::FromString(str));
        }
    }
}

void UW_AddUser::ValidatePWText(const FText& Text)
{
    FString str = Text.ToString();

    if (str.Len() > 32)
    {
        str = str.Left(32);
        Txt_Pass->SetText(FText::FromString(str));
    }
}