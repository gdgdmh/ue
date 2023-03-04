// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VsEnemySpawnManagementSubsytem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UVsEnemySpawnManagementSubsytem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UVsEnemySpawnManagementSubsytem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

};
