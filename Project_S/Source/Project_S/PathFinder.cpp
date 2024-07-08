// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinder.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"

APathFinder::APathFinder()
{
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    NavMesh = Cast<ARecastNavMesh>(NavSys ? NavSys->GetMainNavData() : nullptr);
}

bool APathFinder::FindPath(const FVector& StartLocation, const FVector& EndLocation, TArray<FVector>& OutPath)
{
    if (!NavMesh)
        return false;
    FVector Extent = FVector(50.f, 50.f, 250.f);
    NavNodeRef StartID = NavMesh->FindNearestPoly(StartLocation, Extent);
    NavNodeRef EndID = NavMesh->FindNearestPoly(EndLocation, Extent);

    TSharedPtr<PathNode> StartNode = MakeShared<PathNode>();
    NavMesh->GetPolyCenter(StartID, StartNode->PolyLocation);
    StartNode->HCost = Heuristic(StartLocation, EndLocation);

    TSharedPtr<PathNode> EndNode = MakeShared<PathNode>();
    NavMesh->GetPolyCenter(EndID, EndNode->PolyLocation);

    TArray<TSharedPtr<PathNode>> OpenSet;
    TArray<NavNodeRef> ClosedSet;

    OpenSet.Add(StartNode);

    while (OpenSet.Num() > 0)
    {
        TSharedPtr<PathNode> CurrentNode = OpenSet[0];
        OpenSet.RemoveAt(0);

        if (CurrentNode->PolyLocation.Equals(EndNode->PolyLocation))
        {
            while (CurrentNode)
            {
                OutPath.Insert(CurrentNode->PolyLocation, 0);
                CurrentNode = CurrentNode->Parent;
            }
            OutPath[0] = StartLocation;
            if (OutPath.Num() == 1)
            {
                OutPath.Add(EndLocation);
            }
            else
            {
                OutPath.Last() = EndLocation;
            }
            OutPath = ClearingPath(OutPath);
            return true;
        }
        NavNodeRef ClosedID = NavMesh->FindNearestPoly(CurrentNode->PolyLocation, Extent);
        ClosedSet.Add(ClosedID);

        TArray<NavNodeRef> Neighbors;
        NavNodeRef CurID = NavMesh->FindNearestPoly(CurrentNode->PolyLocation, Extent);
        NavMesh->GetPolyNeighbors(CurID, Neighbors);
        float BestCost = FLT_MAX;
        for (const NavNodeRef& Neighbor : Neighbors)
        {
            if (ClosedSet.Contains(Neighbor)) continue;
            FVector NeighborCenter;
            NavMesh->GetPolyCenter(Neighbor, NeighborCenter);
            TSharedPtr<PathNode> NeighborNode = MakeShared<PathNode>(NeighborCenter);
            float tentativeGCost = Heuristic(CurrentNode->PolyLocation, NeighborCenter) + CurrentNode->GCost + Heuristic(NeighborCenter, EndLocation);
            if (tentativeGCost < BestCost)
            {
                BestCost = tentativeGCost;
                NeighborNode->Parent = CurrentNode;
                NeighborNode->GCost = tentativeGCost;
                NeighborNode->HCost = Heuristic(NeighborCenter, EndLocation);

                if (!OpenSet.Contains(NeighborNode))
                    OpenSet.Insert(NeighborNode, 0);
            }
        }
    }
    return false;
}

TArray<FVector> APathFinder::FindPolyPoint(const FVector& FindLoc)
{
    if (!NavMesh)
        return TArray<FVector>();
    TArray<FVector> AllPoint;
    FVector Extent = FVector(50.f, 50.f, 250.f);
    NavNodeRef CurID = NavMesh->FindNearestPoly(FindLoc, Extent);
    TArray<FVector> PolyVerts;
    if (NavMesh->GetPolyVerts(CurID, PolyVerts))
    {
        for (const FVector& PolyVert : PolyVerts)
        {
            AllPoint.Add(PolyVert);
        }
    }

    return AllPoint;
}

TArray<FVector> APathFinder::ClearingPath(const TArray<FVector> OutPath)
{
    if (!NavMesh)
        return TArray<FVector>();
    TArray<FVector> ClearPath;
    TArray<FVector> Paths = OutPath;
    FVector DummyVector;
    int32 NowLoc = 0;
    ClearPath.Add(OutPath[NowLoc]);
    for (const FVector OutPa : OutPath)
    {
        TArray<FVector> Pathss;

        Pathss = FindPolyPoint(OutPa);
        for (const FVector Path1 : Pathss)
        {
            Paths.Add(Path1);
        }
    }
    Paths.Insert(OutPath[0], 0);
    Paths.Insert(OutPath.Last(), Paths.Num());
    while (NowLoc < Paths.Num() - 1)
    {
        int32 BestLoc = NowLoc;
        float BestCost = FLT_MAX;
        for (int32 j = NowLoc + 1; j < Paths.Num(); ++j)
        {
            if (!NavMesh->NavMeshRaycast(NavMesh, Paths[NowLoc], Paths[j], DummyVector, nullptr))
            {
                float CurrentCost = Heuristic(Paths[0], Paths[NowLoc]) + Heuristic(Paths[NowLoc], Paths[j]) + Heuristic(Paths[j], Paths.Last());
                if (CurrentCost < BestCost)
                {
                    BestLoc = j;
                    BestCost = CurrentCost;
                }
            }
        }

        if (BestLoc == NowLoc)
        {
            // 더 이상 이동할 수 없으면 종료
            break;
        }

        NowLoc = BestLoc;
        if(!ClearPath.Contains(Paths[NowLoc]))
            ClearPath.Add(Paths[NowLoc]);
    }
    ClearPath.RemoveAt(0);
    if (ClearPath.Last() != Paths.Last())
    {
        ClearPath.Add(Paths.Last());
    }
    return ClearPath;
}
