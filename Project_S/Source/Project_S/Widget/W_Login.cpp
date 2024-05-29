// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Login.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Project_S/S_StructureAll.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Controllers/LoginController.h"
#include "Project_S/Widget/W_AddUser.h"
#include "Project_S/Instance/S_GameInstance.h"

UW_Login::UW_Login(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_AddUser.WBP_AddUser_C'"));
    if (UW.Succeeded())
    {
        UAddUser_Widget = UW.Class;
    }
}

void UW_Login::NativeConstruct()
{
    // 버튼 클릭 시 OnLoginButtonClicked 함수 호출을 설정합니다.
    if (Btn_Login)
        Btn_Login->OnClicked.AddDynamic(this, &UW_Login::OnLogin);
    if (Btn_AddUser)
        Btn_AddUser->OnClicked.AddDynamic(this, &UW_Login::OnAddUser);
    if (Text_ID)
        Text_ID->OnTextCommitted.AddDynamic(this, &UW_Login::IDCommitted);
    if (Text_Pass)
        Text_Pass->OnTextCommitted.AddDynamic(this, &UW_Login::IDCommitted);
}

FReply UW_Login::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Enter || InKeyEvent.GetKey() == EKeys::Virtual_Accept)
    {
        OnLogin();
        return FReply::Handled();
    }

    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

bool UW_Login::ValidateLogin(const FString& Username, const FString& Password)
{
    auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (MyGameInstance)
    {
        auto UserData = StaticCastSharedPtr<FUserID>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_UserIDData)->GetMyData(Username));
        if (UserData.IsValid())
        {
            return Username == UserData.Get()->ID && Password == UserData.Get()->Password;
        }
    }
    return false;
}

void UW_Login::IDCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    if (CommitMethod == ETextCommit::OnEnter)
    {
        OnLogin();
    }
}

void UW_Login::OnLogin()
{
    FString Username = Text_ID->GetText().ToString();
    FString Password = Text_Pass->GetText().ToString();

    if (Username != "" && Password != "")
    {
        if (ValidateLogin(Username, Password))
        {
            ALoginController* PlayerController = Cast<ALoginController>(UGameplayStatics::GetPlayerController(this, 0));
            if (PlayerController)
            {
                PlayerController->LoginSuccessful(Username);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("ID : %s , Pass: %s"), *Username, *Password);
        }
    }
}
void UW_Login::OnAddUser()
{
    if (UAddUser_Widget)
    {
        W_AddUser = CreateWidget<UW_AddUser>(GetWorld(), UAddUser_Widget);
        if (W_AddUser)
        {
            W_AddUser->AddToViewport();
        }
    }
}

