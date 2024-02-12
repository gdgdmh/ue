// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Common/ProjectUserWidget.h"

#include "RpgCardHpGaugeUserWidget.h"

#include "RpgCardPlayerInfoUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgCardPlayerInfoUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHpText(FText Text);

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<URpgCardHpGaugeUserWidget> HpGauge;

};
