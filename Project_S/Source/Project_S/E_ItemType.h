// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum class E_ItemType : uint8
{
	E_Weapon UMETA(DisplayName = "Weapon"),
	E_Etc UMETA(DisplayName = "Etc"),
};
