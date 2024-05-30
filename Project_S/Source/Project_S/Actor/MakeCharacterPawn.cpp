// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeCharacterPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Instance/S_GameInstance.h"

// Sets default values
AMakeCharacterPawn::AMakeCharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->CastShadow = false;
	Mesh->SetRelativeRotation(FRotator(0.f, -30.f, 0.f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeLocation(FVector(55.f, -70.f, 80.f));
	CameraBoom->SetRelativeRotation(FRotator(-10.f, -90.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMakeCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	LoadData("Warrior");
	SetActorLocation(FVector(230.f, 120.f, 20.f));
	SetActorRotation(FRotator(0.f, 90.f, 0.f));
}

void AMakeCharacterPawn::SetMesh(TSoftObjectPtr<USkeletalMesh> _Mesh, TSoftClassPtr<UAnimInstance> _Anim)
{
	USkeletalMesh* MeshPath = _Mesh.LoadSynchronous();
	if (MeshPath)
	{
		Mesh->SetSkeletalMesh(MeshPath);
		Mesh->SetAnimInstanceClass(_Anim.LoadSynchronous());
		Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void AMakeCharacterPawn::LoadData(const FString& _ClassName)
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

void AMakeCharacterPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ClassData.IsValid())
		ClassData.Reset();
}
void AMakeCharacterPawn::SetMeshRotation()
{
	Mesh->SetRelativeRotation(FRotator(0.f, -30.f, 0.f));
}

