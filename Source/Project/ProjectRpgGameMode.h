// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectGameModeBase.h"
#include "ProjectRpgGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectRpgGameMode : public AProjectGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectRpgGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};
