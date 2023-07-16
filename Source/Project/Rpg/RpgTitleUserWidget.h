// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"
#include "Components/Button.h"
#include "RpgTitleUserWidget.generated.h"

enum class ERpgTitleUserWidgetSelectType : uint8
{
	Start,
	Test,

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgTitleUserWidgetSelectType, ERpgTitleUserWidgetSelectType::Num)

DECLARE_DELEGATE_OneParam(FRpgTitleDelegate, ERpgTitleUserWidgetSelectType)

/**
 * 
 */
UCLASS()
class PROJECT_API URpgTitleUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable)
		void OnClickedEventStartButton();

	UFUNCTION(BlueprintCallable)
		void OnClickedEventTestButton();

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UButton> StartButton;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UButton> TestButton;

	FRpgTitleDelegate RpgTitleDelegate;

};
