// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CPPRpgTargetType.h"

#include "RpgAttackParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgAttackParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgAttackParameter(const FObjectInitializer& ObjectInitializer);


private:
	// 対象
	CPPRpgTargetType TargetType;

	// 攻撃力
	//int32 AttackPower;
};
