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
	WidgetInteractionComponent->InteractionDistance = 500.f; // 상호작용 거리 설정
	WidgetInteractionComponent->bEnableHitTesting = true;
	WidgetInteractionComponent->bShowDebug = true;
	WidgetInteractionComponent->DebugColor = FColor::Orange;
}

// Called every frame
void ALobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (WidgetInteractionComponent)
    {
        // 마우스 클릭 처리
        ALobbyController* PlayerController = Cast<ALobbyController>(GetController());
        if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
            WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
        else
            WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);

        // 마우스 이동 처리
        FVector2D MousePosition;
        if (PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
            WidgetInteractionComponent->SetCustomHitResult(WidgetInteractionComponent->GetLastHitResult());
    }
}

