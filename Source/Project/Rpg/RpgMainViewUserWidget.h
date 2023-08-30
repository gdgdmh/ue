// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"

#include "Cd/Widget/RpgCardPlayerInfoUserWidget.h"

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

	URpgMainViewUserWidget(const FObjectInitializer& ObjectInitializer);



	FRpgMainViewClickNextButtonDelegate& GetClickNextButtonDelegate();
	FRpgMainViewClickTurnEndButtonDelegate& GetClickTurnEndButtonDelegate();

protected:
	virtual void NativeConstruct() override;

public:
	void SetHpText(FText Text);

public:
	UFUNCTION(BlueprintCallable)
		void OnClickTurnEndButton();

	UFUNCTION(BlueprintCallable)
		void OnClickNextButton();

	// UI bind
public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<URpgCardPlayerInfoUserWidget> PlayerInfo;

	// delegate
protected:
	FRpgMainViewClickNextButtonDelegate ClickNextButtonDelegate;
	FRpgMainViewClickTurnEndButtonDelegate ClickTurnEndButtonDelegate;
};
