// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"
#include "DrawDebugHelpers.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Project_S/Component/C_SkillComponent.h"

// Sets default values
AFirstCharacter::AFirstCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;
	Stat = CreateDefaultSubobject<US_StatComponent>(TEXT("STAT"));
	Skill = CreateDefaultSubobject<UC_SkillComponent>(TEXT("SKILL"));
}

float AFirstCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);
	return DamageAmount;
}

void AFirstCharacter::SetMyColor(int32 _MyColor)
{
	MyColor = _MyColor;
}

void AFirstCharacter::SetCharID(FString _CharID)
{
	CharID = _CharID;
}

void AFirstCharacter::SetSaveLocation(FVector _SaveLocation)
{
	SaveLocation = _SaveLocation;
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


