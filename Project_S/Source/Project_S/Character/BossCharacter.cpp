// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Controllers/EnemyAIController.h"

ABossCharacter::ABossCharacter()
{
	SetBossMesh();
}

void ABossCharacter::SetBossMesh()
{
	//SetActorScale3D(FVector(5.f, 5.f, 5.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	FVector MeshLocation = FVector(0.f, 0.f, -300.f);
	FRotator MeshRotator = FRotator(0.f, -90.f, 0.f);
	GetMesh()->SetRelativeLocationAndRotation(MeshLocation, MeshRotator);
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));
	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/Ancient_Golem/Demo/Boss_AnimBP.Boss_AnimBP_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));
	if (MainAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
	}
	HeadWheel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadWheel"));
	Drill = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drill"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WheelAsset(TEXT("SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Head_Wheel.SK_Ancient_Golem_Head_Wheel'"));
	if (WheelAsset.Succeeded())
	{
		HeadWheel->SetSkeletalMesh(WheelAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DrillAsset(TEXT("SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels'"));
	if (DrillAsset.Succeeded())
	{
		Drill->SetSkeletalMesh(DrillAsset.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> WheelAnimAsset(TEXT("AnimBlueprint'/Game/Ancient_Golem/Animation/SK_Ancient_Golem_Head_Wheel_Skeleton_AnimBlueprint.SK_Ancient_Golem_Head_Wheel_Skeleton_AnimBlueprint_C'"));
	if (WheelAnimAsset.Succeeded())
	{
		HeadWheel->SetAnimInstanceClass(WheelAnimAsset.Class);
	}
	HeadWheel->SetupAttachment(GetMesh(), TEXT("headSocket"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> DrillAnimAsset(TEXT("AnimBlueprint'/Game/Ancient_Golem/Animation/SK_Ancient_Golem_Moving_Wheels_Skeleton_AnimBlueprint.SK_Ancient_Golem_Moving_Wheels_Skeleton_AnimBlueprint_C'"));
	if (DrillAnimAsset.Succeeded())
	{
		Drill->SetAnimInstanceClass(DrillAnimAsset.Class);
	}
	Drill->SetupAttachment(GetMesh(), TEXT("spine_03Socket"));
}

void ABossCharacter::AnyMove()
{
	SetActorLocation(NowAIController->GetUser()->GetActorLocation());
}

void ABossCharacter::Make_Projectile()
{
}

void ABossCharacter::Set_Projectile()
{
}
