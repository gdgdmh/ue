// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleStatusParameter.h"
#include "RpgBattleStatus.generated.h"

/**
 * バトルステータス管理
 */
UCLASS()
class PROJECT_API URpgBattleStatus : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattleStatus();

	void Reset();

	void Copy(const URpgBattleStatus& Source);

	void OutputLog();

	/**
	 * ステータスの重複チェック
	 * true: 重複している
	 */
	bool CheckDuplicate(ERpgBattleStatusType Type);

	/**
	 * 指定されたステータスを含んでいるかチェック
	 * true:含んでいる
	 */
	bool CheckContains(ERpgBattleStatusType Type);

	/**
	 * ステータスの取得
	 * CheckContainsでデータが存在することを確認してから取得すること
	 * 存在しない場合はassertで止まる
	 */
	FRpgBattleStatusParameter& GetStatus(ERpgBattleStatusType Type);

	/**
	* パラメーターなしでステータスを追加
	* 重複したステータスは追加されない
	*/
	bool AddStatus(ERpgBattleStatusType Type);

	bool AddStatusParameter(const FRpgBattleStatusParameter& Parameter);

public:
	TArray<FRpgBattleStatusParameter> Statuses; // 複数のステータスパラメーター
};
