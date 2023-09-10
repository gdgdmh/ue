// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CPPRpgActionType.h"

#include "RpgAttackParameter.h"
#include "RpgDefenceParameter.h"

#include "RpgActionParameter.generated.h"

/**
 * 行動パラメーター
 */
UCLASS()
class PROJECT_API URpgActionParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgActionParameter(const FObjectInitializer& ObjectInitializer);

	void SetActionType(ERpgActionType Type);
	void SetAttackTarget(ERpgTargetType TargetType);
	void SetAttackPower(int32 Power);

	void SetDefenceTarget(ERpgTargetType TargetType);
	void SetDefencePower(int32 Power);

	ERpgActionType GetActionType() const;
	ERpgTargetType GetAttackTarget() const;
	int32 GetAttackPower() const;

	ERpgTargetType GetDefenceTarget() const;
	int32 GetDefencePower() const;


protected:
	// アクションタイプ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ERpgActionType ActionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<URpgAttackParameter> AttackParameter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<URpgDefenceParameter> DefenceParameter; 
};
