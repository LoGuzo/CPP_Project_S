// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	ProjectileMovementComponent->bRotationFollowsVelocity = true; //ȸ��
	//ȸ����
	ProjectileMovementComponent->bShouldBounce; //ƨ��
	ProjectileMovementComponent->Bounciness = 0.3f; //ƨ�� ��
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
}

void AS_Projectile::SetProjectile()
{
}

