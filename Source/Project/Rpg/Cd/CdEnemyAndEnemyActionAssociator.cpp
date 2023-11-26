// Fill out your copyright notice in the Description page of Project Settings.


#include "CdEnemyAndEnemyActionAssociator.h"

UCdEnemyAndEnemyActionAssociator::UCdEnemyAndEnemyActionAssociator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EnemyAndEnemyActionData()
	, Enemies()
	, TableProgressIndices()
{
}

// 敵の行動テーブルの設定
void UCdEnemyAndEnemyActionAssociator::SetEnemyTables(TObjectPtr<UEnemyAndEnemyActionDataParameter> Parameter)
{
	check(Parameter);
	EnemyAndEnemyActionData = Parameter;
}

// 敵と行動テーブルの関連付け
void UCdEnemyAndEnemyActionAssociator::Set(TObjectPtr<UCdCharacterBase>& Enemy)
{
	// 関連付けできないことは想定してないのでサイズ0はASSERT
	check(EnemyAndEnemyActionData);
	check(EnemyAndEnemyActionData.Get()->Size() > 0);

	// 対応した敵のテーブルをランダムで取得
	FEnemyAndEnemyActionDataTable Table;
	if (!EnemyAndEnemyActionData.Get()->GetRandomEnemyActionData(Table, Enemy.Get()->GetParameter()->GetType()))
	{
		check(false);
		return;
	}

	// テーブルを設定
	EnemyActionTables.Add(Table);

	// 敵を追加
	Enemies.Add(Enemy);

	// テーブル進行度indexを追加
	TableProgressIndices.Add(0);

	// EnemiesとEnemyActionTablesとTableProgressIndicesはサイズが一致している必要がある
	check(Enemies.Num() == EnemyActionTables.Num());
	check(Enemies.Num() == TableProgressIndices.Num());
}

// アクションの取得
bool UCdEnemyAndEnemyActionAssociator::GetAction(FEnemyActionDataTable& Out, const TObjectPtr<UCdCharacterBase>& Target)
{
	int32 Index = -1;
	{
		// 指定された敵のindexを取得
		const int32 Size = Enemies.Num();
		for (int32 i = 0; i < Size; ++i)
		{
			if (Enemies[i] == Target)
			{
				Index = i;
				break;
			}
		}
	}

	if (Index < 0)
	{
		// 指定された敵が見つからない
		return false;
	}

	// テーブル進行度を取得
	check((0 <= Index) && (Index < TableProgressIndices.Num()));
	int32 TableProgressIndex = TableProgressIndices[Index];

	// 行動テーブルからアクションを取得
	check((0 <= Index) && (Index < EnemyActionTables.Num()));
	Out = EnemyActionTables[Index].GetDatas()[TableProgressIndex];

	return true;
}

// すべての敵のテーブル進行度を進める
void UCdEnemyAndEnemyActionAssociator::ForwardIndices()
{
	const int32 Size = TableProgressIndices.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		ForwardTableIndices(i);
	}
}

// 指定Indexのテーブル進行度を進める
void UCdEnemyAndEnemyActionAssociator::ForwardTableIndices(int32 TargetIndex)
{
	check((0 <= TargetIndex) && (TargetIndex < EnemyActionTables.Num()));
	// 対象の行動テーブルのサイズを取得する
	const int32 Size = EnemyActionTables[TargetIndex].EnemyActionDatas.Num();
	if (Size == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UCdEnemyAndEnemyActionAssociator::ForwardTableIndices Size == 0"));
		return;
	}

	check((0 <= TargetIndex) && (TargetIndex < TableProgressIndices.Num()));
	int32 CurrentIndex = TableProgressIndices[TargetIndex];
	if ((CurrentIndex + 1) < Size)
	{
		// +1して大丈夫なのでそのまま加算
		TableProgressIndices[TargetIndex] = CurrentIndex + 1;
	}
	else
	{
		// 配列サイズをオーバーしてしまうのでループ
		TableProgressIndices[TargetIndex] = 0;
	}
}
