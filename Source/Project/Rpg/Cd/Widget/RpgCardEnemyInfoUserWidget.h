// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Common/ProjectUserWidget.h"


#include "RpgCardHpGaugeUserWidget.h"
#include "SelectFrameUserWidget.h"
#include "NextActionUserWidget.h"

#include "RpgCardEnemyInfoUserWidget.generated.h"

// Delegate
// 押されたときのDelegate
DECLARE_DELEGATE_OneParam(FRpgCardEnemyInfoUserWidgetOnClickDelegate, TObjectPtr<URpgCardEnemyInfoUserWidget>)

/**
 * 
 */
UCLASS()
class PROJECT_API URpgCardEnemyInfoUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void OnClick();


public:
	void SetHpText(FText Text);
	void SetHp(int32 Hp, int32 MaxHp);

	void SetAction(ECdEnemyActionType Type);

	// 全体の非表示
	void Hide();

	// 選択フレームの表示非表示
	void HideSelectFrame();
	void ShowSelectFrame();
	bool IsShowingSelectFrame() const;

	FRpgCardEnemyInfoUserWidgetOnClickDelegate& GetOnClickDelegate();

public:
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<URpgCardHpGaugeUserWidget> HpGauge;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<USelectFrameUserWidget> SelectFrame;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UNextActionUserWidget> NextAction;


	FRpgCardEnemyInfoUserWidgetOnClickDelegate EnemyInfoUserWidgetOnClickDelegate;
};
