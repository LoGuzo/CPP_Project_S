// Fill out your copyright notice in the Description page of Project Settings.


#include "RedPotionActor.h"

ARedPotionActor::ARedPotionActor()
{
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
    ItemMesh->SetupAttachment(RootComponent);
}

void ARedPotionActor::BeginPlay()
{
    Super::BeginPlay();
}

void ARedPotionActor::SetW_Mesh(TSoftObjectPtr<UStreamableRenderAsset> _ItemMesh) 
{
    UStaticMesh* MeshPath = Cast<UStaticMesh>(_ItemMesh.LoadSynchronous());
    if (MeshPath)
    {
        ItemMesh->SetStaticMesh(MeshPath);
    }
    ItemMesh->SetCollisionProfileName(TEXT("NoCollision"));
}