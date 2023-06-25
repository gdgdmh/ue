// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "VsWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AVsWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	AVsWorldSettings();

public:
	UPROPERTY(EditAnywhere)
		bool bUseEnemySpawnSubsystem;

	UPROPERTY(EditAnyWhere)
		bool bUseVsUserWidgetSubsystem;

};
