// Fill out your copyright notice in the Description page of Project Settings.


#include "SUtils.h"

float SUtils::SDistance(const FVector Pos, const FVector OtherPos)
{
	FVector pos = Pos - OtherPos;
	float value = FMath::Sqrt((pos.X * pos.X) + (pos.Y * pos.Y) + (pos.Z * pos.Z));
	return value;
}
