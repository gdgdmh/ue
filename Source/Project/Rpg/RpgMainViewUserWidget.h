// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"

#include "Cd/Widget/RpgCardPlayerInfoUserWidget.h"
#include "Cd/Widget/RpgCardEnemyInfoUserWidget.h"
#include "CdCharacterBase.h"

#include "Components/HorizontalBox.h"

#include "../CPPEnemyType.h"

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
	// キャラが死んでいるか
	bool IsDead() const;

	void SetWidgetHp();

	void DeadWidget();


protected:
	// data ptr
	UPROPERTY()
		TObjectPtr<UCdCharacterBase> Enemy;
	// widget
	UPROPERTY()
		TObjectPtr<URpgCardEnemyInfoUserWidget> UserWidget;
};

/**
 * 敵表示情報まとめ
 */
USTRUCT()
struct FEnemyDisplayInfos
{
	GENERATED_BODY()

public:
	FEnemyDisplayInfos()
	{
	}

	void Add(const FEnemyDisplayInfo& Info);
	void Remove(int32 Index);

	bool Find(const TObjectPtr<UCdCharacterBase>& Target);
	int32 FindAt(const TObjectPtr<UCdCharacterBase>& Target);
	FEnemyDisplayInfo& At(int32 Index);
	int32 Size() const { return Infos.Num(); }

protected:
	TArray<FEnemyDisplayInfo> Infos;
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

	void SetEnemyView(const TArray<TObjectPtr<UCdCharacterBase> >& Enemies);

public:
	UFUNCTION(BlueprintCallable)
		void OnClickTurnEndButton();

	UFUNCTION(BlueprintCallable)
		void OnClickNextButton();

protected:

	FEnemyDisplayInfos EnemyDisplayInfos;

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
