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
// 押されたときのDelegate
DECLARE_DELEGATE_TwoParams(FRpgCardEnemyInfoUserWidgetClickDelegate, TObjectPtr<UCdCharacterBase>, TObjectPtr<URpgCardEnemyInfoUserWidget>)

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

	TObjectPtr<UCdCharacterBase> GetEnemy();
	const TObjectPtr<UCdCharacterBase> GetEnemy() const;
	TObjectPtr<URpgCardEnemyInfoUserWidget> GetUserWidget();
	const TObjectPtr<URpgCardEnemyInfoUserWidget> GetUserWidget() const;
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

	void FindEnemy(TObjectPtr<UCdCharacterBase>& Enemy, const TObjectPtr<URpgCardEnemyInfoUserWidget> Widget);

	FEnemyDisplayInfo& At(int32 Index);
	const FEnemyDisplayInfo& At(int32 Index) const;

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
	FRpgCardEnemyInfoUserWidgetClickDelegate& GetClickCardEnemyInfoDelegate();

protected:
	virtual void NativeConstruct() override;

public:
	void SetHpText(FText Text);

	void SetEnemyView(const TArray<TObjectPtr<UCdCharacterBase> >& Enemies);

	// 敵が選択されたとき
	void OnSelectEnemyInfo(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget);

	// 選択状態か
	bool IsEnemySelected(const TObjectPtr<URpgCardEnemyInfoUserWidget> Widget) const;
	// 選択状態にする
	void SetEnemySelected(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget);
	// 非選択状態にする
	void SetEnemyUnselected(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget);

	void SetAllEnemyUnselected();

	// いくつ選択状態になっているか
	int32 GetEnemySelecatedNum() const;

public:
	UFUNCTION(BlueprintCallable)
		void OnClickTurnEndButton();

	UFUNCTION(BlueprintCallable)
		void OnClickNextButton();

	//UFUNCTION(BlueprintCallable)
	//	void OnClickNextButton();

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
	FRpgCardEnemyInfoUserWidgetClickDelegate ClickCardEnemyInfoDelegate;
};
