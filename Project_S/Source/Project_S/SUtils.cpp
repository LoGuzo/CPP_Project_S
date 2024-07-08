// Fill out your copyright notice in the Description page of Project Settings.


#include "SUtils.h"

float SUtils::SDistance(const FVector Pos, const FVector OtherPos)
{
	FVector AfterPos = FVector(Pos.X, Pos.Y, 0);
	FVector AfterOtherPos = FVector(OtherPos.X, OtherPos.Y, 0);

	FVector pos = AfterPos - AfterOtherPos;
	float value = FMath::Sqrt((pos.X * pos.X) + (pos.Y * pos.Y) + (pos.Z * pos.Z));
	return value;
}

int32 SUtils::RandRange(int32 Min, int32 Max)
{
	if (Max < Min)
		return Min;

	return FMath::RandRange(Min, Max);
}
float SUtils::RandRange(float Min, float Max)
{
	if (Max < Min)
		return Min;

	return FMath::RandRange(Min, Max);
}