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

    // To add mapping context
    virtual void BeginPlay() override;

    /** Called for movement input */
    virtual void Move(const FInputActionValue& Value) override;

    /** Called for looking input */
    virtual void Look(const FInputActionValue& Value) override;

    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#if 0
protected:
    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* FollowCamera;

    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputMappingContext* DefaultMappingContext;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* LookAction;
#endif
protected:

    //ProjectCharacter�ƒ�`���Ԃ肵�Ă���̂ł����������
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
