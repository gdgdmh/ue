// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "ProjectWorldSettings.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API AProjectWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	AProjectWorldSettings();

public:
	UPROPERTY(EditAnywhere)
		bool bUseEnemySpawnSubsystem;

	UPROPERTY(EditAnyWhere)
		bool bUseUserWidgetSubsystem;

};
