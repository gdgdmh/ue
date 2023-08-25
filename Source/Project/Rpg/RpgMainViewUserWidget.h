// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"
#include "RpgMainViewUserWidget.generated.h"

// Delegate
// NextButtonが押されたときのDelegate
DECLARE_DELEGATE(FRpgMainViewClickNextButtonDelegate)
// TurnEndButtonが押されたときのDelegate
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
