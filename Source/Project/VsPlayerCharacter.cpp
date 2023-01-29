// Fill out your copyright notice in the Description page of Project Settings.


#include "VsPlayerCharacter.h"
#include "WeaponKnife.h"

AVsPlayerCharacter::AVsPlayerCharacter()
{    //ProjectCharacter�ƒ�`���Ԃ肵�Ă���̂ł����������
#if 0
	ProjectileClass = AWeaponKnife::StaticClass();
	//Initialize fire rate
	FireRate = 0.25f;
	bIsFiringWeapon = false;
#endif
}

//ProjectCharacter�ƒ�`���Ԃ肵�Ă���̂ł����������
#if 0

void AVsPlayerCharacter::StartFire()
{
    if (!bIsFiringWeapon)
    {
        bIsFiringWeapon = true;
        UWorld* World = GetWorld();
        World->GetTimerManager().SetTimer(FiringTimer, this, &AVsPlayerCharacter::StopFire, FireRate, false);
        HandleFire();
    }
}

void AVsPlayerCharacter::StopFire()
{
    //ProjectCharacter�ƒ�`���Ԃ肵�Ă���̂ł����������
    bIsFiringWeapon = false;
}

void AVsPlayerCharacter::HandleFire_Implementation()
{
    FVector spawnLocation = GetActorLocation() + (GetActorRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
    FRotator spawnRotation = GetActorRotation();

    FActorSpawnParameters spawnParameters;
    spawnParameters.Instigator = GetInstigator();
    spawnParameters.Owner = this;

    AWeaponKnife* spawnedProjectile = GetWorld()->SpawnActor<AWeaponKnife>(spawnLocation, spawnRotation, spawnParameters);
}
#endif