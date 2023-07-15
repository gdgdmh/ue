// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectGameModeBase.h"

#include "ProjectUserWidget.h"
#include "Rpg/RpgTitleUserWidget.h"

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

public:
	void OnDelegateRpgTitleUserWidgetSelect(ERpgTitleUserWidgetSelectType Type);

private:
	void SetTitleUI();
	void CleanupTitleUI();

private:
	void SetMainUI();
	void CleanupMainUI();
	

private:
	// ƒ^ƒCƒgƒ‹‚ÌUserWidget‚Ü‚Æ‚ß
	UPROPERTY()
		TArray< TObjectPtr<UProjectUserWidget> > TitleProjectUserWidgets;

private:
	UPROPERTY()
		TArray< TObjectPtr<UProjectUserWidget> > MainProjectUserWidgets;

};
