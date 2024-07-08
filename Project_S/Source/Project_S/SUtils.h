// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace SUtils
{
	float SDistance(const FVector Pos, const FVector OtherPos);

	// 오버로딩
	int32 RandRange(int32 Min, int32 Max);//정수 랜덤값

	float RandRange(float Min, float Max);//실수 랜덤값
}
