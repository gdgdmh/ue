// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopShootWeaponBase.h"

ALoopShootWeaponBase::ALoopShootWeaponBase()
{
}

ALoopShootWeaponBase::ALoopShootWeaponBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ALoopShootWeaponBase::~ALoopShootWeaponBase()
{
}

// 発射前処理
void ALoopShootWeaponBase::ProcessShootBefore()
{
	ShootBeforeDispacher.Broadcast();
}