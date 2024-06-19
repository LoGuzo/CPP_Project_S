// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordWeapon.h"
#include "DrawDebugHelpers.h"
#include "Project_S/Character/FirstCharacter.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ASwordWeapon::ASwordWeapon() {
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	Weapon->SetupAttachment(RootComponent);
}

void ASwordWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASwordWeapon::SetW_Mesh(TSoftObjectPtr<UStreamableRenderAsset> _ItemMesh) {
	USkeletalMesh* MeshPath =  Cast<USkeletalMesh>(_ItemMesh.LoadSynchronous());
    if (MeshPath)
    {
        Weapon->SetSkeletalMesh(MeshPath);
    }
    Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	
}
