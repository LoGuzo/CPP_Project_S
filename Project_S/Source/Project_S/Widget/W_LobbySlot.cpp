// Fill out your copyright notice in the Description page of Project Settings.


#include "W_LobbySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Project_S/MappingClass.h"
#include "Project_S/Actor/LobbyCharacter.h"
#include "Project_S/Instance/S_GameInstance.h"


UW_LobbySlot::UW_LobbySlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("Material'/Game/ThirdPersonCPP/Blueprints/Material/M_RenderTarget.M_RenderTarget'"));
	if (MaterialFinder.Succeeded())
	{
		RenderTargetMaterial = MaterialFinder.Object;
	}
}
void UW_LobbySlot::SetCharName(FString _CharName)
{
	CharName = _CharName;
}

void UW_LobbySlot::SetIndex(int32 _SlotIndex)
{
	SlotIndex = _SlotIndex;
}

void UW_LobbySlot::SetCharacterImage(UTextureRenderTarget2D* RenderTarget)
{
	if (Img_Char && RenderTarget)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(RenderTargetMaterial, this);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetTextureParameterValue(FName("RenderTarget"), RenderTarget);

			Img_Char->SetBrushFromMaterial(DynamicMaterial);
		}
	}
}

void UW_LobbySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_LobbySlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetWidget();
}

void UW_LobbySlot::NativeDestruct()
{
	Super::NativeDestruct();
	if (UserData.IsValid())
		UserData.Reset();
	if (LobbyCharacter != nullptr)
		LobbyCharacter->Destroy();
}

void UW_LobbySlot::SetWidget()
{
	CharacterTypeMapping = new MappingClass();
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (CharName != "")
		{
			UserData = StaticCastSharedPtr<FMyCharacterData>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_MyChar)->GetMyData(CharName));
			if (UserData.IsValid())
			{
				LobbyCharacter = GetWorld()->SpawnActor<ALobbyCharacter>(ALobbyCharacter::StaticClass(), FVector(100.f * SlotIndex, 500.f, 500.f), FRotator::ZeroRotator);
				LobbyCharacter->LoadData(CharacterTypeMapping->GetCharacterDescription(UserData.Pin()->Type));
				Btn_Create->SetVisibility(ESlateVisibility::Hidden);
				Txt_Name->SetText(FText::FromString(UserData.Pin()->CharID));
				Txt_Lvl->SetText(FText::FromString(FString::Printf(TEXT("Lv : %d"), UserData.Pin()->Level)));
				Txt_Class->SetText(FText::FromString(CharacterTypeMapping->GetCharacterDescription(UserData.Pin()->Type)));
				SetCharacterImage(LobbyCharacter->GetRenderTarget());
				Img_Char->SetVisibility(ESlateVisibility::Visible);
				Box_Info->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			Img_Char->SetVisibility(ESlateVisibility::Hidden);
			Btn_Create->SetVisibility(ESlateVisibility::Visible);
			Box_Info->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
