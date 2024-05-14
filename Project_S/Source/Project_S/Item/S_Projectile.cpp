// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Misc/OutputDeviceNull.h"

// Sets default values
AS_Projectile::AS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(10.f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true; //È¸Àü
	//È¸Àü°ª
	ProjectileMovementComponent->bShouldBounce; //Æ¨±è
	ProjectileMovementComponent->Bounciness = 0.3f; //Æ¨±è °ª
}

// Called when the game starts or when spawned
void AS_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_Projectile::FireInDirection(const FVector& Direction)
{
	FString str = "test";
	FOutputDeviceNull ar;
	CallFunctionByNameWithArguments(*str, ar, NULL, true);
}

void AS_Projectile::SetProjectile()
{
	// ºí·çÇÁ¸°Æ® Å¬·¡½º
	/*if (ProjectileClass == nullptr)
		return;*/
	FVector CameraLocation;
	FRotator CameraRotation;
	FVector Offset;

	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector SpawnLocation = CameraLocation + FTransform(CameraRotation).TransformVector(Offset);

	FRotator SpawnRotator = CameraRotation;
	SpawnRotator.Pitch += 10.f;
	UWorld* world = GetWorld();

	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		/*SpawnParams.Instigator = this;

		AS_Projectile* Projectile = world->SpawnActor<AS_Projectile>(ProjectilClass, SpawnLocation, SpawnRotator, SpawnParams);

		if (Projectile)
		{
			FVector Direction = SpawnRotator.Vector();
			Projectile->FireInDirection(Direction);
		}*/
	}
}

