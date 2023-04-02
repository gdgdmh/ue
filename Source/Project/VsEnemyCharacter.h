// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCharacter.h"
#include "VsEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AVsEnemyCharacter : public AProjectCharacter
{
	GENERATED_BODY()
	
public:
	AVsEnemyCharacter();

protected:

	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


public:
	UFUNCTION(BlueprintCallable)
		void SubHealth(int32 sub);

	UFUNCTION(BlueprintCallable)
		void SubHealthFloat(float sub);

	UFUNCTION(BlueprintCallable)
		void AddHealth(int32 add);

	UFUNCTION(BlueprintCallable)
		bool IsAlive() const;

protected:
	void NormalizationHealth();
	void CheckDestroy();

	// É_ÉÅÅ[ÉWWBPèàóù
	void ShowDamage(float DamageAmount);

protected:

	UPROPERTY(EditAnywhere)
		int32 MaxHealth;	// ç≈ëÂHP

	UPROPERTY(EditAnywhere)
		int32 Health;	// HP

	UPROPERTY()
		bool bIsAlive;	// ê∂ë∂ÇµÇƒÇ¢ÇÈÇ©

};
