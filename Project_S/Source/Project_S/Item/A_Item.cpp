// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Item.h"
#include "Project_S/Character/UserCharacter.h"

// Sets default values
AA_Item::AA_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemCom = CreateDefaultSubobject<UC_ItemComponent>(TEXT("ITEMCOM"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISION"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f)); 
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AA_Item::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AA_Item::EndOverlap);


	RootComponent = BoxCollision;
}

void AA_Item::SetName(FString _Name)
{
	Name = _Name;
}

void AA_Item::SetType(FString _Type)
{
	Type = _Type;
}

void AA_Item::BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass()->GetSuperClass() == AUserCharacter::StaticClass())
		{
			auto userCharacter = Cast<AUserCharacter>(OtherActor);
			userCharacter->SetCurItem(this);
		}

	}
}

void AA_Item::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass()->GetSuperClass() == AUserCharacter::StaticClass())
		{
			auto userCharacter = Cast<AUserCharacter>(OtherActor);
			userCharacter->SetCurItem(nullptr);
		}

	}
}
