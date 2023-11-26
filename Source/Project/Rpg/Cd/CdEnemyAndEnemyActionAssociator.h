// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../CdCharacterBase.h"
#include "EnemyActionParameter.h"
#include "CdEnemyAndEnemyActionAssociator.generated.h"

/**
 * 敵と行動テーブルの紐づけ
 */
UCLASS()
class PROJECT_API UCdEnemyAndEnemyActionAssociator : public UObject
{
	GENERATED_BODY()
	
public:
	UCdEnemyAndEnemyActionAssociator(const FObjectInitializer& ObjectInitializer);

	// 敵の行動テーブル集合体の設定
	void SetEnemyTables(TObjectPtr<UEnemyAndEnemyActionDataParameter> Parameter);

	// 敵と行動テーブルの関連付け
	void Set(TObjectPtr<UCdCharacterBase>& Enemy);

	// 指定された敵のアクションの取得
	bool GetAction(FEnemyActionDataTable& Out, const TObjectPtr<UCdCharacterBase>& Target);

	// すべての敵のテーブル進行度を進める
	void ForwardIndices();

private:

	// 指定Indexのテーブル進行度を進める
	void ForwardTableIndices(int32 TargetIndex);

public:

	// 敵と敵の行動パラメーター
	UPROPERTY()
	TObjectPtr<UEnemyAndEnemyActionDataParameter> EnemyAndEnemyActionData;

	// 敵
	UPROPERTY()
		TArray<TObjectPtr<UCdCharacterBase> > Enemies;

	// 敵と紐づく行動テーブル(EnemiesのindexとEnemyActionTableのindexが対応している)
	UPROPERTY()
		TArray<FEnemyAndEnemyActionDataTable> EnemyActionTables;

	// テーブル進行度(Indexが対象の敵)
	UPROPERTY()
		TArray<int32> TableProgressIndices;				// テーブル進行度index(本来はこのクラスではなくて分離すべきだが妥協)
};
