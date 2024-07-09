// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPotal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Instance/S_GameInstance.h"

// Sets default values
ALevelPotal::ALevelPotal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollsion"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	LevelName = "BossMap";

	ConstructorHelpers::FObjectFinder<UParticleSystem>PS(TEXT("ParticleSystem'/Game/DreamscapeSeries/DreamscapeTower/Effects/P_TeleportSparks.P_TeleportSparks'"));
	if (PS.Succeeded())
	{
		Particle = PS.Object;
	}
}

void ALevelPotal::SetLevelName(const FString& _LevelName)
{
	LevelName = _LevelName;
}

// Called when the game starts or when spawned
void ALevelPotal::BeginPlay()
{
	Super::BeginPlay();

	ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, FTransform(GetTargetLocation()), false, EPSCPoolMethod::ManualRelease, true);
}

void ALevelPotal::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(ParticleComponent)
		ParticleComponent->ReleaseToPool();
	GetWorldTimerManager().ClearTimer(UnusedHandle);
}

void ALevelPotal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!character)
		return;
	BPFunction();
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ALevelPotal::NextLevel, 3.f, false);
}

void ALevelPotal::BPFunction()
{
	FString str = "FadeFunc";
	FOutputDeviceNull ar;
	CallFunctionByNameWithArguments(*str, ar, nullptr, true);
}

void ALevelPotal::NextLevel()
{
	auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		MyGameInstance->NextLoadingLevel(LevelName);
	}
}
