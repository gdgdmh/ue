// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VsUserWidgetSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UVsUserWidgetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UVsUserWidgetSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

};
