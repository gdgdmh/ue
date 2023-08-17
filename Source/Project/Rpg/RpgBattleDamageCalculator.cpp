﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleDamageCalculator.h"

void URpgBattleDamageCalculator::Calc(int32& Damage, TWeakObjectPtr<URpgBattleCharacterBase> Attacker, TWeakObjectPtr<URpgBattleCharacterBase> Target,
	ERpgBattleCommandType CommandType)
{
	Damage = 0;
	if (!Attacker.IsValid())
	{
		return;
	}
	if (!Target.IsValid())
	{
		return;
	}

	if (CommandType == ERpgBattleCommandType::Attack)
	{
		Damage = CalcBaseDamage(Attacker.Get()->GetParameter().Get()->GetAttackPower(), Target.Get()->GetParameter().Get()->GetDefencePower());
		return;
	}
	// 今の所、他にはまだ対応してない
}

int32 URpgBattleDamageCalculator::CalcBaseDamage(int32 AttackPower, int32 DefencePower)
{
	// いったんドラクエベースの計算式にする(ランダム要素や他のものに関してはおいておく)
	// 攻撃力÷2－守備力÷4＝ダメージ基礎値
	// ダメージ基礎値 ÷16＋1（端数切捨）
	return (AttackPower / 2) - (DefencePower / 4);
}