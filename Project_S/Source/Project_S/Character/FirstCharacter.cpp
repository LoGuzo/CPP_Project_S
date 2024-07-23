// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Component/C_SkillComponent.h"

// Sets default values
AFirstCharacter::AFirstCharacter()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;

	SetReplicateMovement(true);
	GetMesh()->SetIsReplicated(true);

	Stat = CreateDefaultSubobject<US_StatComponent>(TEXT("STAT"));

	Skill = CreateDefaultSubobject<UC_SkillComponent>(TEXT("SKILL"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> SoundObject(TEXT("SoundWave'/Game/Mannequin/Animations/Sound/hit_sound.hit_sound'"));
	if (SoundObject.Succeeded())
		ParticleSound = SoundObject.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackP(TEXT("ParticleSystem'/Game/ParagonGreystone/FX/Particles/Greystone/Abilities/Deflect/FX/P_Greystone_Deflect_Remove.P_Greystone_Deflect_Remove'"));
	if (AttackP.Succeeded())
		HitParticleEffect = AttackP.Object;
}

float AFirstCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->OnAttacked(DamageAmount);

	if (Stat->GetHp() <= 0)
		IsDead = true;

	if (HitParticleEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleEffect, GetActorLocation());

	if (ParticleSound && AudioComponent)
	{
		AudioComponent->SetSound(ParticleSound);
		AudioComponent->Play();
	}

	return DamageAmount;
}

void AFirstCharacter::SetCharID(const FString& _CharID)
{
	CharID = _CharID;
}

void AFirstCharacter::SetSaveLocation(FVector _SaveLocation)
{
	SaveLocation = _SaveLocation;
}

void AFirstCharacter::UseSkill(const FString& _SkillName)
{
	if (HasAuthority())
		Multi_UseSkill(_SkillName);
	else
		Server_UseSkill(_SkillName);
}

void AFirstCharacter::Server_UseSkill_Implementation(const FString& _SkillName)
{
	Multi_UseSkill(_SkillName);
}

bool AFirstCharacter::Server_UseSkill_Validate(const FString& SkillName)
{
	return true;
}

void AFirstCharacter::Multi_UseSkill_Implementation(const FString& _SkillName)
{
}

void AFirstCharacter::MeleeAttackCheck(float _Range)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	float AttackRange = _Range * GetActorScale3D().X;
	float AttackRadius = 50.f * GetActorScale3D().X;
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		this->GetActorLocation(),
		this->GetActorLocation() + (this->GetActorForwardVector()) * (AttackRange),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	FVector Vec = this->GetActorForwardVector() * AttackRange;
	FVector Center = this->GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor = FColor::Red;

	for (FHitResult hitResult : HitResults)
	{
		if (bResult && hitResult.Actor.IsValid())
		{
			auto Enemy = Cast<AFirstCharacter>(hitResult.Actor.Get());
			if (Enemy)
			{
				if (MyCharType == E_CharacterType::E_Monster)
				{
					if (Enemy->MyCharType == E_CharacterType::E_User) {
						FDamageEvent DamageEvent;
						hitResult.Actor->TakeDamage(this->Stat->GetAttack(), DamageEvent, this->GetController(), this);
						DrawColor = FColor::Green;
						break;
					}
				}
				if (MyCharType == E_CharacterType::E_User)
				{
					if (Enemy->MyCharType == E_CharacterType::E_Monster) {
						FDamageEvent DamageEvent;
						hitResult.Actor->TakeDamage(this->Stat->GetAttack(), DamageEvent, this->GetController(), this);
						DrawColor = FColor::Green;
						break;
					}
				}
			}
		}
	}
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);
}

void AFirstCharacter::ScopeAttackCheck(float _Range)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	float AttackRange = _Range * GetActorScale3D().X;
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
				if (MyCharType == E_CharacterType::E_Monster)
				{
					if (Enemy->MyCharType == E_CharacterType::E_User) {
						FDamageEvent DamageEvent;
						hitResult.Actor->TakeDamage(this->Stat->GetAttack(), DamageEvent, this->GetController(), this);
						DrawColor = FColor::Green;
					}
				}
				else if(MyCharType == E_CharacterType::E_User)
				{
					if (Enemy->MyCharType == E_CharacterType::E_Monster) {
						FDamageEvent DamageEvent;
						hitResult.Actor->TakeDamage(this->Stat->GetAttack(), DamageEvent, this->GetController(), this);
						DrawColor = FColor::Green;
					}
				}
			}
		}
	}
	DrawDebugSphere(GetWorld(), Center, AttackRange, 10, DrawColor, false, 2.f);
}

void AFirstCharacter::ShotAttackCheck()
{
	
}

void AFirstCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFirstCharacter, Stat);
	DOREPLIFETIME(AFirstCharacter, CharID);
}



