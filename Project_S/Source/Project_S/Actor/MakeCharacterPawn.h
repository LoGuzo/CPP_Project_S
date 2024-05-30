// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MakeCharacterPawn.generated.h"

struct FCharacterClass;

UCLASS()
class PROJECT_S_API AMakeCharacterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMakeCharacterPawn();
	void LoadData(const FString& _ClassName);

	USkeletalMeshComponent* GetMesh() { return Mesh; }

	void SetMeshRotation();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	TWeakPtr<FCharacterClass> ClassData;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	void SetMesh(TSoftObjectPtr<USkeletalMesh> _Mesh, TSoftClassPtr<UAnimInstance> _Anim);
};
