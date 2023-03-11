// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawnVsEnemy.h"
#include "VsEnemySpawnManagementSubsytem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UVsEnemySpawnManagementSubsytem : public UGameInstanceSubsystem /*UWorldSubsystem*/
{
	GENERATED_BODY()

public:
	UVsEnemySpawnManagementSubsytem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void Start(FTimerManager& TimerManager);

private:
	void StartTimer(FTimerManager& TimerManager);
	void OnTimerElapsed();

private:
	FTimerHandle TimerHandle;
	UPROPERTY()
		TObjectPtr<ASpawnVsEnemy> SpawnVsEnemy;
	bool bIsActive;
};
