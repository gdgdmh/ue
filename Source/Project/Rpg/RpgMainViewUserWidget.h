// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"

#include "Cd/Widget/RpgCardPlayerInfoUserWidget.h"
#include "Cd/Widget/RpgCardEnemyInfoUserWidget.h"
#include "CdCharacterBase.h"

#include "Components/HorizontalBox.h"

#include "RpgMainViewUserWidget.generated.h"

// Delegate
// NextButtonが押されたときのDelegate
DECLARE_DELEGATE(FRpgMainViewClickNextButtonDelegate)
// TurnEndButtonが押されたときのDelegate
DECLARE_DELEGATE(FRpgMainViewClickTurnEndButtonDelegate)

/**
 * 敵表示情報
 */
USTRUCT()
struct FEnemyDisplayInfo
{
	GENERATED_BODY()

public:
	FEnemyDisplayInfo()
	{
		Enemy = nullptr;
		UserWidget = nullptr;
	}
	void SetCharacter(TObjectPtr<UCdCharacterBase> EnemyData);
	void SetUserWidget(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget);
	// 同一オブジェクトかチェック
	bool IsSameCharacter(const TObjectPtr<UCdCharacterBase>& EnemyData) const;
	bool IsSameUserWidget(const TObjectPtr<URpgCardEnemyInfoUserWidget>& Widget) const;

protected:
	// data ptr
	UPROPERTY()
		TObjectPtr<UCdCharacterBase> Enemy;
	// widget
	UPROPERTY()
		TObjectPtr<URpgCardEnemyInfoUserWidget> UserWidget;

};

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

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UHorizontalBox> EnemyArea;

	// delegate
protected:
	FRpgMainViewClickNextButtonDelegate ClickNextButtonDelegate;
	FRpgMainViewClickTurnEndButtonDelegate ClickTurnEndButtonDelegate;
};
