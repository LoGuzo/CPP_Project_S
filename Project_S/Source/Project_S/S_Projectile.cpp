// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Projectile.h"

// Sets default values
AS_Projectile::AS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

void AS_Projectile::SetProjectile()
{
}

