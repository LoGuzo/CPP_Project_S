// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordWeapon.h"
#include "DrawDebugHelpers.h"
#include "FirstCharacter.h"
#include "UserCharacter.h"
#include "S_StatComponent.h"

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
		ECollisionChannel::ECC_EngineTraceChannel2,
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
			HitResult.Actor->TakeDamage(User->Stat->GetAttack(), DamageEvent, User->GetController(), this);
		}
	}
}