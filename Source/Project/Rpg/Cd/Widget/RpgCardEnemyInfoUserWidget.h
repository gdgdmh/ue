// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectUserWidget.h"

#include "RpgCardHpGaugeUserWidget.h"
#include "SelectFrameUserWidget.h"

#include "RpgCardEnemyInfoUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgCardEnemyInfoUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHpText(FText Text);
	void SetHp(int32 Hp, int32 MaxHp);

	void Hide();

	void HideSelectFrame();
	void ShowSelectFrame();
	bool IsShowingSelectFrame() const;

public:
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<URpgCardHpGaugeUserWidget> HpGauge;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<USelectFrameUserWidget> SelectFrame;

};
