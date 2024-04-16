// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordWeapon.h"

ASwordWeapon::ASwordWeapon() {
    PrimaryActorTick.bCanEverTick = false;
    SetW_Mesh();
}

void ASwordWeapon::SetW_Mesh() {
    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
    RootComponent = Weapon;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("SkeletalMesh'/Game/Weapons/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'"));
    if (SK_WEAPON.Succeeded())
    {
        Weapon->SetSkeletalMesh(SK_WEAPON.Object);
    }
    Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}