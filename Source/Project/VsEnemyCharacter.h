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

public:
	UFUNCTION(BlueprintCallable)
		void SubHealth(int32 sub);

	UFUNCTION(BlueprintCallable)
		void AddHealth(int32 add);

	UFUNCTION(BlueprintCallable)
		bool IsAlive() const;

protected:
	void NormalizationHealth();

protected:

	UPROPERTY(EditAnywhere)
		int32 MaxHealth;	// ç≈ëÂHP

	UPROPERTY(EditAnywhere)
		int32 Health;	// HP

	UPROPERTY()
		bool bIsAlive;	// ê∂ë∂ÇµÇƒÇ¢ÇÈÇ©

};
