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

void URpgBattleStatus::Copy(const URpgBattleStatus& Source)
{
	Reset();
	for (const auto& Status : Source.Statuses)
	{
		AddStatusParameter(Status);
	}
}

void URpgBattleStatus::OutputLog()
{
	// 何もないパターン
	if (Statuses.Num() == 0)
	{
		// 何もない状態は想定してない
		UE_LOG(LogTemp, Log, TEXT("Status:Unknown"));
		check(false);
		return;
	}

	// 通常しかないパターン
	if (Statuses.Num() == 1)
	{
		if (CheckContains(ERpgBattleStatusType::None))
		{
			UE_LOG(LogTemp, Log, TEXT("Status:通常"));
			return;
		}
	}

	// 死亡しているパターン
	if (CheckContains(ERpgBattleStatusType::Dead))
	{
		UE_LOG(LogTemp, Log, TEXT("Status:死亡"));
		return;
	}

	FString Status = TEXT("Status");
	if (CheckContains(ERpgBattleStatusType::Poisoned))
	{
		Status += TEXT(":毒");
	}
	if (CheckContains(ERpgBattleStatusType::Paralyzed))
	{
		Status += TEXT(":麻痺");
	}
	if (CheckContains(ERpgBattleStatusType::Confused))
	{
		Status += TEXT(":混乱");
	}
	if (CheckContains(ERpgBattleStatusType::Asleep))
	{
		Status += TEXT(":睡眠");
	}
	if (CheckContains(ERpgBattleStatusType::Blind))
	{
		Status += TEXT(":盲目");
	}
	if (CheckContains(ERpgBattleStatusType::Stunned))
	{
		Status += TEXT(":気絶");
	}
	if (CheckContains(ERpgBattleStatusType::Charmed))
	{
		Status += TEXT(":魅了");
	}
	if (CheckContains(ERpgBattleStatusType::Silenced))
	{
		Status += TEXT(":沈黙");
	}
	if (CheckContains(ERpgBattleStatusType::Bleeding))
	{
		Status += TEXT(":出血");
	}
	if (CheckContains(ERpgBattleStatusType::Stoned))
	{
		Status += TEXT(":石化");
	}
	if (CheckContains(ERpgBattleStatusType::Frozen))
	{
		Status += TEXT(":凍結");
	}
	if (CheckContains(ERpgBattleStatusType::Burning))
	{
		Status += TEXT(":炎上");
	}
	if (CheckContains(ERpgBattleStatusType::Berserk))
	{
		Status += TEXT(":狂化");
	}
	if (CheckContains(ERpgBattleStatusType::Taunted))
	{
		Status += TEXT(":挑発");
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *Status);
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

bool URpgBattleStatus::AddStatusParameter(const FRpgBattleStatusParameter& Parameter)
{
	// 重複ステータスなら何もしない
	if (CheckDuplicate(Parameter.Type))
	{
		return false;
	}
	Statuses.Add(Parameter);
	return true;
}