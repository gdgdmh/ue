// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectUserWidget.h"
#include "RpgCardHpGaugeUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgCardHpGaugeUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:

	URpgCardHpGaugeUserWidget(const FObjectInitializer& ObjectInitializer);

	void SetHpText(FText Text);

	// UI bind
public:
	UPROPERTY(BlueprintReadWrite)
		FText HpText;

/*
	UPROPERTY(BlueprintReadWrite)
		FString DamageText;

*/

};
