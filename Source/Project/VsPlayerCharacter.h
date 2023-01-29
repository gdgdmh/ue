// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCharacter.h"
#include "VsPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AVsPlayerCharacter : public AProjectCharacter
{
	GENERATED_BODY()

public:
    AVsPlayerCharacter();

protected:

    //ProjectCharacterÇ∆íËã`Ç©Ç‘ÇËÇµÇƒÇ¢ÇÈÇÃÇ≈Ç¢Ç¡ÇΩÇÒè¡Ç∑
#if 0
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay|Weapon")
        TSubclassOf<class AWeaponKnife> ProjectileClass;

    /** Delay between shots in seconds. Used to control fire rate for your test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input.*/
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
        float FireRate;

    /** If true, you are in the process of firing projectiles. */
    bool bIsFiringWeapon;

    /** Function for beginning weapon fire.*/
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
        void StartFire();

    /** Function for ending weapon fire. Once this is called, the player can use StartFire again.*/
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
        void StopFire();

    /** Server function for spawning projectiles.*/
    UFUNCTION(Server, Reliable)
        void HandleFire();

    /** A timer handle used for providing the fire rate delay in-between spawns.*/
    FTimerHandle FiringTimer;
#endif

};
