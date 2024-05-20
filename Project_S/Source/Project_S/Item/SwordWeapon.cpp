// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordWeapon.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Project_S/Character/FirstCharacter.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ASwordWeapon::ASwordWeapon() {
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	Weapon->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackP(TEXT("ParticleSystem'/Game/ParagonGreystone/FX/Particles/Greystone/Abilities/Deflect/FX/P_Greystone_Deflect_Remove.P_Greystone_Deflect_Remove'"));
	if (AttackP.Succeeded())
	{
		HitParticleEffect = AttackP.Object;
	}
}

void ASwordWeapon::BeginPlay()
{
	Super::BeginPlay();
	ItemCom->SetItem("BlackSword");
	SetName(ItemCom->GetItemName());
	SetW_Mesh(ItemCom->GetItemMesh());
	SetType(ItemCom->GetType());

}

void ASwordWeapon::SetW_Mesh(TSoftObjectPtr<UStreamableRenderAsset> _ItemMesh) {
	USkeletalMesh* MeshPath =  Cast<USkeletalMesh>(_ItemMesh.LoadSynchronous());
    if (MeshPath)
    {
        Weapon->SetSkeletalMesh(MeshPath);
    }
    Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	
}

void ASwordWeapon::AttackCheck(class AUserCharacter* _UserCharacter) {
	auto User = Cast<AFirstCharacter>(_UserCharacter);
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(User);
	float AttackRange = 150.f;
	float AttackRadius = 50.f;
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		User->GetActorLocation(),
		User->GetActorLocation() + (User->GetActorForwardVector()) * (AttackRange),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	FVector Vec = User->GetActorForwardVector() * AttackRange;
	FVector Center = User->GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;
	if (bResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);

	if (bResult && HitResult.Actor.IsValid())
	{
		auto Enemy = Cast<AFirstCharacter>(HitResult.Actor.Get());
		if (Enemy) {
			FDamageEvent DamageEvent;
			UGameplayStatics::SpawnEmitterAttached(HitParticleEffect,User->GetMesh(), FName("Paticle"));
			HitResult.Actor->TakeDamage(User->Stat->GetAttack(), DamageEvent, User->GetController(), this);
		}
	}
}
