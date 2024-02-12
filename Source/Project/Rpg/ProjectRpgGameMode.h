﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectGameModeBase.h"

#include "../Common/ProjectUserWidget.h"
#include "RpgTitleUserWidget.h"
#include "RpgMainViewUserWidget.h"

#include "RpgBattleParty.h"
#include "RpgBattleManager.h"
#include "ActionCardList.h"

#include "ProjectRpgGameMode.generated.h"

// 前方宣言
class URpgMainUserWidget;

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectRpgGameMode : public AProjectGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectRpgGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

public:
	void OnDelegateRpgTitleUserWidgetSelect(ERpgTitleUserWidgetSelectType Type);
private:
	void SetTitleUI();
	void CleanupTitleUI();

private:
	void SetMainUI();
	void CleanupMainUI();
	
	void InitializeBattleManager();

private:

	void RpgMainViewOnClickNextButton();
	void RpgMainViewOnClickTurnEndButton();
	void RpgMainViewOnClickCardEnemyInfoDelegate(TObjectPtr<UCdCharacterBase> Enemy, TObjectPtr<URpgCardEnemyInfoUserWidget> Widget);

	void BattleManagerOnChangePlayerInfo();
	void BattleManagerOnChangeEnemyInfo();
	void BattleManagerOnChangeProcessState(ERpgBattleProcessState State);

	//void RpgMainOnClickNextButton();

private:
	void UpdatePlayerInfo();
	void UpdateEnemyInfo();
	void UpdateProcessState(ERpgBattleProcessState State);
	void OutputStateLog(ERpgBattleProcessState BeforeState, ERpgBattleProcessState AfterState);

private:
	// タイトルのUserWidgetまとめ
	UPROPERTY()
		TArray< TObjectPtr<UProjectUserWidget> > TitleProjectUserWidgets;

private:
	// RpgMainのまとめ
	UPROPERTY()
		TArray< TObjectPtr<UProjectUserWidget> > MainProjectUserWidgets;

	UPROPERTY()
		TObjectPtr<URpgMainUserWidget> RpgMainWidget;

	UPROPERTY()
		TObjectPtr<URpgMainViewUserWidget> RpgMainViewUserWidget;

	// パーティ
	UPROPERTY()
		TObjectPtr<URpgBattleParty> AllyParty;

	UPROPERTY()
		TObjectPtr<URpgBattleParty> EnemyParty;
	// バトルマネージャー
	UPROPERTY()
		TObjectPtr<URpgBattleManager> BattleManager;
	// カードリスト
	UPROPERTY()
		TObjectPtr<UActionCardList> CardList;

	//TWeakObjectPtr<UActionCard> AAA;
	//UPROPERTY()
	//	bool bTasking;
};