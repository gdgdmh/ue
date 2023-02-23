// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopShootKnife.h"
#include "WeaponKnife.h"

ALoopShootKnifer::ALoopShootKnifer()
{
}

ALoopShootKnifer::ALoopShootKnifer(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ALoopShootKnifer::~ALoopShootKnifer()
{
}

// ”­ŽËˆ—
void ALoopShootKnifer::ProcessShoot()
{
	UWorld* World = /*GEngine->*/GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("not Shoooooot"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Shoooooot"));
	AWeaponKnife* spawnedProjectile = World->SpawnActor<AWeaponKnife>(ShootParameter->GetLocation(), ShootParameter->GetRotation(), ShootParameter->GetSpawnParameters());
	//AWeaponKnife* spawnedProjectile = GetWorld()->SpawnActor<AWeaponKnife>(ShootParameter->GetLocation(), ShootParameter->GetRotation(), ShootParameter->GetSpawnParameters());
}
