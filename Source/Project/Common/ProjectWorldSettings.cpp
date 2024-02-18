// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectWorldSettings.h"

AProjectWorldSettings::AProjectWorldSettings()
{
	// フラグ配列の初期化
	if (Flags.Num() == 0)
	{
		for (const auto& ArrayIndex : TEnumRange<EWorldSettingsFlagType>())
		{
			Flags.Add(ArrayIndex, false);
		}
	}
	// デフォルト値
	// UserWidgetSubsystemは有効にして使わなくても特に変なことは起こらないので有効にしておく
	Flags[EWorldSettingsFlagType::UseUserWidgetSubsystem] = true;
}

// フラグ配列の指定のタイプが有効(true)になっているか
bool AProjectWorldSettings::IsEnabled(EWorldSettingsFlagType Type) const
{
	return Flags[Type];
}