// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace SUtils
{
	float SDistance(const FVector Pos, const FVector OtherPos);

	// �����ε�
	int32 RandRange(int32 Min, int32 Max);//���� ������

	float RandRange(float Min, float Max);//�Ǽ� ������
}
