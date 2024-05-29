// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Instance/S_GameInstance.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetRelativeLocation(FVector(0.f, 200.f, 140.f));
	SceneCapture->SetRelativeRotation(FRotator(-10.f, -90.f, 0.f));
	SceneCapture->SetupAttachment(RootComponent);
	SceneCapture->FOVAngle = 60.f;

	// Render target 생성 및 Scene Capture Component에 설정
	RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("RenderTarget"));
	RenderTarget->InitAutoFormat(512, 512);
	SceneCapture->TextureTarget = RenderTarget;
	SceneCapture->CaptureSource = SCS_SceneColorHDR;
}

void ALobbyCharacter::SetMesh(TSoftObjectPtr<USkeletalMesh> _Mesh, TSoftClassPtr<UAnimInstance> _Anim)
{
	USkeletalMesh* MeshPath = _Mesh.LoadSynchronous();
	if (MeshPath)
	{
		Mesh->SetSkeletalMesh(MeshPath);
		Mesh->SetAnimInstanceClass(_Anim.LoadSynchronous());
		Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void ALobbyCharacter::LoadData(const FString& _ClassName)
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (_ClassName != "") {
			ClassData = StaticCastSharedPtr<FCharacterClass>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_CharClassData)->GetMyData(_ClassName));
			if (ClassData.IsValid())
			{
				SetMesh(ClassData.Pin()->ClassMesh, ClassData.Pin()->ClassAnim);
			}
		}
	}
}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ClassData.IsValid())
		ClassData.Reset();
}
