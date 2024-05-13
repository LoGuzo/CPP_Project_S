// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class E_State : uint8
{
	E_None,
	E_Search,
	E_Move,
	E_Attack,
	E_Reset,
};