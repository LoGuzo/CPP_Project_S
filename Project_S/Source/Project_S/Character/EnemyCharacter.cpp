// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Project_S/EnemyAIController.h"
#include "Project_S/Component/S_StatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project_S/Widget/OnlyHpBar.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBP_OnlyHpBar.WBP_OnlyHpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 500.f));
	}
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnlyHpBar->SetRenderOpacity(1.f);
	return DamageAmount;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Stat->SetLevel(2);
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HpBar->InitWidget();

	OnlyHpBar = Cast<UOnlyHpBar>(HpBar->GetUserWidgetObject());
	if (OnlyHpBar)
	{
		OnlyHpBar->BindHp(Stat);
		OnlyHpBar->SetRenderOpacity(0.f);
	}
}
