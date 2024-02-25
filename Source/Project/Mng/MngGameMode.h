// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MngGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMngGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMngGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

};
