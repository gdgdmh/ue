﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectGameModeBase.h"

#include "ProjectUserWidget.h"
#include "Rpg/RpgTitleUserWidget.h"

#include "Rpg/RpgBattleParty.h"
#include "Rpg/RpgBattleManager.h"

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
	void RpgMainOnClickNextButton();

private:
	// タイトルのUserWidgetまとめ
	UPROPERTY()
		TArray< TObjectPtr<UProjectUserWidget> > TitleProjectUserWidgets;

private:
	// RpgMainのまとめ
	UPROPERTY()
		TArray< TObjectPtr<UProjectUserWidget> > MainProjectUserWidgets;

	TObjectPtr<URpgMainUserWidget> RpgMainWidget;

	// パーティ
	UPROPERTY()
		TWeakObjectPtr<URpgBattleParty> AllyParty;

	UPROPERTY()
		TWeakObjectPtr<URpgBattleParty> EnemyParty;
	// バトルマネージャー
	UPROPERTY()
		TObjectPtr<URpgBattleManager> BattleManager;
		//TWeakObjectPtr<URpgBattleManager> BattleManager;
};
