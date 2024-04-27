// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_S/Component/C_ItemComponent.h"
#include "Components/BoxComponent.h"
#include "A_Item.generated.h"

UCLASS(Abstract)
class PROJECT_S_API AA_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Item();
protected:
	UFUNCTION()
	virtual void SetW_Mesh() PURE_VIRTUAL(AWeaponActor::SetW_Mesh, ;);

	UFUNCTION()
	void SetName(FString _Name);

	UFUNCTION()
	void SetType(FString _Type);

	FString GetName() { return Name; }

	FString GetType() { return Type; }

	UPROPERTY(VisibleAnywhere, Category = Component)
	UC_ItemComponent* ItemCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	
	UPROPERTY(VisibleAnywhere)
	FString Name;

	UPROPERTY(VisibleAnywhere)
	FString Type;

public:	
	// Called every frame
	UBoxComponent* GetBoxCollision() { return BoxCollision; }
	UC_ItemComponent* GetC_ItemComponent(){ return ItemCom; }

};
