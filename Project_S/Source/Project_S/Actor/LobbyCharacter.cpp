// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetRelativeLocation(FVector(0.f, 120.f, 115.f));
	SceneCapture->SetRelativeRotation(FRotator(-10.f, -90.f, 0.f));
	SceneCapture->SetupAttachment(RootComponent);

	// Render target 생성 및 Scene Capture Component에 설정
	RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("RenderTarget"));
	RenderTarget->InitAutoFormat(512, 512);
	SceneCapture->TextureTarget = RenderTarget;
	SceneCapture->CaptureSource = SCS_SceneColorSceneDepth;
}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
}