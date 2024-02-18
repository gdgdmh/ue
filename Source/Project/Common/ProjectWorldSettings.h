// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"

#include "CPPWorldSettingsFlagType.h"
#include "ProjectWorldSettings.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API AProjectWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	AProjectWorldSettings();

public:
	// フラグ配列の指定のタイプが有効(true)になっているか
	bool IsEnabled(EWorldSettingsFlagType Type) const;

public:

	// フラグ配列(配列サイズは変更禁止)
	UPROPERTY(EditAnywhere, EditFixedSize)
		TMap<EWorldSettingsFlagType, bool> Flags;
};
