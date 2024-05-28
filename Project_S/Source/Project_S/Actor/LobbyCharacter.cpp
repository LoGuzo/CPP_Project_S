// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyCharacter.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	LobbyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LobbyWidget"));
	LobbyWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_CharacterLobby.WBP_CharacterLobby_C'"));
	if (UW.Succeeded())
	{
		LobbyWidget->SetWidgetClass(UW.Class);
		LobbyWidget->SetDrawSize(FVector2D(200.f, 200.f));
		LobbyWidget->SetRelativeLocation(FVector(0.f, 60.f, 105.f));
		LobbyWidget->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
	LobbyWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	LobbyWidget->InitWidget();
}