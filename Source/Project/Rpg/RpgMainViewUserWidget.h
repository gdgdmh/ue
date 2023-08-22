// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"
#include "RpgMainViewUserWidget.generated.h"

// Delegate
// NextButton‚ª‰Ÿ‚³‚ê‚½‚Æ‚«‚ÌDelegate
DECLARE_DELEGATE(FRpgMainViewClickNextButtonDelegate)
// TurnEndButton‚ª‰Ÿ‚³‚ê‚½‚Æ‚«‚ÌDelegate
DECLARE_DELEGATE(FRpgMainViewClickTurnEndButtonDelegate)

/**
 * 
 */
UCLASS()
class PROJECT_API URpgMainViewUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:



	FRpgMainViewClickNextButtonDelegate& GetClickNextButtonDelegate();
	FRpgMainViewClickTurnEndButtonDelegate& GetClickTurnEndButtonDelegate();

public:
	UFUNCTION(BlueprintCallable)
		void OnClickTurnEndButton();

	UFUNCTION(BlueprintCallable)
		void OnClickNextButton();

protected:
	FRpgMainViewClickNextButtonDelegate ClickNextButtonDelegate;
	FRpgMainViewClickTurnEndButtonDelegate ClickTurnEndButtonDelegate;
};
