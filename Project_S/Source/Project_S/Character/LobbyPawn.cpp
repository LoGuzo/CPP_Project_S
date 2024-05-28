// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPawn.h"
#include "Components/WidgetInteractionComponent.h"
#include "Project_S/Controllers/LobbyController.h"

// Sets default values
ALobbyPawn::ALobbyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->SetupAttachment(RootComponent);
	WidgetInteractionComponent->InteractionDistance = 500.f; // ��ȣ�ۿ� �Ÿ� ����
	WidgetInteractionComponent->bEnableHitTesting = true;
	WidgetInteractionComponent->bShowDebug = true;
	WidgetInteractionComponent->DebugColor = FColor::Orange;
}

// Called when the game starts or when spawned
void ALobbyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (WidgetInteractionComponent)
    {
        ALobbyController* PlayerController = Cast<ALobbyController>(GetController());
        // ���콺 Ŭ�� ó��
        if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
        {
            WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
        }
        else
        {
            WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
        }

        // ���콺 �̵� ó��
        FVector2D MousePosition;
        if (PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
        {
            WidgetInteractionComponent->SetCustomHitResult(WidgetInteractionComponent->GetLastHitResult());
        }
    }
}

// Called to bind functionality to input
void ALobbyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

