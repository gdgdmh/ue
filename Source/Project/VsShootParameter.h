// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "VsShootParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AVsShootParameter : public AActor
{
	GENERATED_BODY()

public:
	AVsShootParameter();
	~AVsShootParameter();

public:
	void Copy(AVsShootParameter Parameter);
	void SetLocation(FVector LocationValue);
	void SetRotation(FRotator RotationValue);
	void SetSpawnParameters(FActorSpawnParameters SpawnParametersValue);

	const FVector GetLocation() const;
	const FRotator GetRotation() const;
	const FActorSpawnParameters GetSpawnParameters() const;

private:
	UPROPERTY()
		FVector Location;

	UPROPERTY()
		FRotator Rotation;
	
	FActorSpawnParameters SpawnParameters;
};
