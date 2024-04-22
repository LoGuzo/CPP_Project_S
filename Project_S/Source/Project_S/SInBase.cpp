// Fill out your copyright notice in the Description page of Project Settings.


#include "SInBase.h"
#include "CharacterManager.h"

USInBase::USInBase()
{
}

void USInBase::Init()
{
	Super::Init();
	CharManage = NewObject<UCharacterManager>();
}
