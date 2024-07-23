// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Projectile.h"
#include "DrawDebugHelpers.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Character/FirstCharacter.h"

// Sets default values
AS_Projectile::AS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicateMovement(true);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(30.f);
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = CollisionComponent;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 2500.f;
	ProjectileMovementComponent->MaxSpeed = 2500.f;
	ProjectileMovementComponent->bAutoActivate = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void AS_Projectile::BeginPlay()
{
	Super::BeginPlay();

	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AS_Projectile::SetProjectileOwner(AFirstCharacter* _Owner)
{
	Owner = _Owner;
}

void AS_Projectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AS_Projectile, ProjectileMesh);
}

void AS_Projectile::ScopeAttackCheck(float _Range)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Owner);
	float AttackRange = _Range;
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		this->GetActorLocation(),
		this->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRange),
		Params
	);

	FVector Center = this->GetActorLocation();
	FColor DrawColor = FColor::Red;

	for (FHitResult hitResult : HitResults)
	{
		if (bResult && hitResult.Actor.IsValid())
		{
			auto Enemy = Cast<AFirstCharacter>(hitResult.Actor.Get());
			if (Enemy)
			{
				if (Owner->GetType() == E_CharacterType::E_Monster)
				{
					if (Enemy->GetType() == E_CharacterType::E_User) {
						FDamageEvent DamageEvent;
						hitResult.Actor->TakeDamage(Owner->GetStatCom()->GetAttack(), DamageEvent, Owner->GetController(), this);
						DrawColor = FColor::Green;
					}
				}
				else if (Owner->GetType() == E_CharacterType::E_User)
				{
					if (Enemy->GetType() == E_CharacterType::E_Monster) {
						FDamageEvent DamageEvent;
						hitResult.Actor->TakeDamage(Owner->GetStatCom()->GetAttack(), DamageEvent, Owner->GetController(), this);
						DrawColor = FColor::Green;
					}
				}
			}
		}
	}

	DrawDebugSphere(GetWorld(), Center, AttackRange, 10, DrawColor, false, 2.f);
}

void AS_Projectile::SetParticle_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleEffect, GetActorLocation());
	if (AudioComponent)
		AudioComponent->Play();
}