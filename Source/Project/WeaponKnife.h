// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponKnife.generated.h"

UCLASS()
class PROJECT_API AWeaponKnife : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponKnife();

private:
    static const float LIFE_TIME;   // 発射してから自動で消える時間

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

    UFUNCTION(Category = "Weapon")
        void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    void SetDestroyTimer();
    void OnLifeTimeEnd();

public:
    // Sphere component used to test collision.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class USphereComponent* SphereComponent;

    // Static Mesh used to provide a visual representation of the object.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UStaticMeshComponent* StaticMesh;

    // Movement component for handling projectile movement.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UProjectileMovementComponent* ProjectileMovementComponent;

    // Particle used when the projectile impacts against another object and explodes.
    UPROPERTY(EditAnywhere, Category = "Effects")
        class UParticleSystem* ExplosionEffect;

public:
    //The damage type and damage that will be done by this projectile
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
        TSubclassOf<class UDamageType> DamageType;
    //The damage dealt by this projectile.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
        float Damage;
private:
	int Power;
    bool bIsLifeTimeEnd;
};
