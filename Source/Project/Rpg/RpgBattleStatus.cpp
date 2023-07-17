// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleStatus.h"

URpgBattleStatus::URpgBattleStatus()
{
	Reset();
}

void URpgBattleStatus::Reset()
{
	// 全てクリアしてNoneだけ設定
	Statuses.Empty();

	{
		FRpgBattleStatusParameter Parameter;
		Parameter.Type = ERpgBattleStatusType::None;
		Statuses.Add(Parameter);
	}
}

bool URpgBattleStatus::CheckDuplicate(ERpgBattleStatusType Type)
{
	for (const auto& Status : Statuses)
	{
		if (Status.Type == Type)
		{
			return true;
		}
	}
	return false;
}

bool URpgBattleStatus::CheckContains(ERpgBattleStatusType Type)
{
	return CheckDuplicate(Type);
}

FRpgBattleStatusParameter& URpgBattleStatus::GetStatus(ERpgBattleStatusType Type)
{
	for (FRpgBattleStatusParameter& Status : Statuses)
	{
		if (Status.Type == Type)
		{
			return Status;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("URpgBattleStatus::GetStatus NotHitType"));
	check(false);
	// 警告を防ぐために返しているが本来ここは通らない想定
	return Statuses[0];
}

bool URpgBattleStatus::AddStatus(ERpgBattleStatusType Type)
{
	// 重複ステータスなら何もしない
	if (CheckDuplicate(Type))
	{
		return false;
	}

	FRpgBattleStatusParameter Parameter;
	Parameter.Type = Type;
	Statuses.Add(Parameter);

	return true;
}