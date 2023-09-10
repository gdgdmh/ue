// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionCardAttackParameter.generated.h"

/**
 * カードの攻撃パラメーター
 */
UCLASS()
class PROJECT_API UActionCardAttackParameter : public UObject
{
	GENERATED_BODY()
	
public:
	UActionCardAttackParameter(const FObjectInitializer& ObjectInitializer);

public:
	void SetPawer(int32 Power);
	int32 GetPower() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AttackPower;
};
