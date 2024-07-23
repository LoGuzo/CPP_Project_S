// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LobbyCharacter.generated.h"

struct FCharacterClass;

UCLASS()
class PROJECT_S_API ALobbyCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALobbyCharacter();

	void LoadData(const FString& _ClassName);

	class UTextureRenderTarget2D* GetRenderTarget() { return RenderTarget; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class USceneCaptureComponent2D* SceneCapture;
	class UTextureRenderTarget2D* RenderTarget;

	TWeakPtr<FCharacterClass> ClassData;

	void SetMesh(TSoftObjectPtr<USkeletalMesh> _Mesh, TSoftClassPtr<UAnimInstance> _Anim);
};
