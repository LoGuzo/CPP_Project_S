// Fill out your copyright notice in the Description page of Project Settings.


#include "StaffWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AStaffWeapon::AStaffWeapon() {
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	Weapon->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackP(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_AOE_Fire_CircleAttack.P_AOE_Fire_CircleAttack'"));
	if (AttackP.Succeeded())
	{
		ParticleEffect = AttackP.Object;
	}
	WeaponParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WeaponParticle"));
	WeaponParticle->SetupAttachment(RootComponent);
}

void AStaffWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AStaffWeapon::SetW_Mesh(TSoftObjectPtr<UStreamableRenderAsset> _ItemMesh) {
	USkeletalMesh* MeshPath = Cast<USkeletalMesh>(_ItemMesh.LoadSynchronous());
	if (MeshPath)
	{
		Weapon->SetSkeletalMesh(MeshPath);
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));


	if (ParticleEffect)
	{
		WeaponParticle->AttachToComponent(Weapon, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Particle"));
		WeaponParticle->SetTemplate(ParticleEffect);
		WeaponParticle->Activate();
	}
}

void AStaffWeapon::Fire()
{
}
