// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathFinder.generated.h"


// PathNode
struct PathNode
{
    FVector PolyLocation;

    NavNodeRef PolyID;

    float GCost;

    float HCost;

    TSharedPtr<PathNode> Parent;

    PathNode(FVector _PolyLocation = FVector(), NavNodeRef _PolyID = NavNodeRef())
        : PolyLocation(_PolyLocation), PolyID(_PolyID), GCost(0), HCost(0), Parent(nullptr) {}

    float FCost() const { return GCost + HCost; }
};
/**
 * 
 */
UCLASS()
class PROJECT_S_API APathFinder : public AActor
{
	GENERATED_BODY()

public:
    APathFinder();
    bool FindPath(const FVector& StartLocation, const FVector& EndLocation, TArray<FVector>& OutPath);

private:
    class ARecastNavMesh* NavMesh;

    float Heuristic(FVector a, FVector b) { return FVector::Dist(a, b) * 0.999f; }

    TArray<FVector> FindPolyPoint(const FVector& FindLoc);

    TArray<FVector> ClearingPath(const TArray<FVector> OutPath);
};
