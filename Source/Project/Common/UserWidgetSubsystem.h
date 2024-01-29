// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ProjectUserWidget.h"
#include "UserWidgetSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UUserWidgetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UUserWidgetSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void Add(TObjectPtr<UProjectUserWidget> ProjectUserWidget);
	void Remove(TObjectPtr<UProjectUserWidget> ProjectUserWidget);
	void Clear();

private:
	TArray< TObjectPtr<UProjectUserWidget> > VsUserWidgets;
};
