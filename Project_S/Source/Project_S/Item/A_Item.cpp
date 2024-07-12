// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Item.h"
#include "Project_S/Character/UserCharacter.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AA_Item::AA_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	ItemCom = CreateDefaultSubobject<UC_ItemComponent>(TEXT("ITEMCOM"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISION"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f)); 
	BoxCollision->SetCollisionProfileName(TEXT("Item"));
	BoxCollision->SetSimulatePhysics(true);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AA_Item::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AA_Item::EndOverlap);
	RootComponent = BoxCollision;
}

void AA_Item::SetItem(const FString& _ItemName)
{
	Name = _ItemName;
	OnRep_ItemSet();
}

void AA_Item::OnRep_ItemSet()
{
	ItemCom->SetItem(Name);
	SetW_Mesh(ItemCom->GetItemMesh());
	SetType(ItemCom->GetType());
}

void AA_Item::SetName(const FString& _ItemName)
{
	Name = _ItemName;
	ItemCom->SetItem(Name);
}

void AA_Item::SetType(E_ItemType _Type)
{
	Type = _Type;
}

void AA_Item::BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass() == AUserCharacter::StaticClass())
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
		if (OtherActor->GetClass() == AUserCharacter::StaticClass())
		{
			auto userCharacter = Cast<AUserCharacter>(OtherActor);
			userCharacter->SetCurItem(nullptr);
		}
	}
}

void AA_Item::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle DropTimeHandle;
	GetWorldTimerManager().SetTimer(DropTimeHandle, this, &AA_Item::SetDrop, 0.5f, false);
}

void AA_Item::SetDrop()
{
	BoxCollision->SetSimulatePhysics(false);
}

void AA_Item::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AA_Item, Name);
}