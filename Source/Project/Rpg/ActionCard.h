// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "RpgActionParameter.h"

#include "ActionCard.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UActionCard : public UObject
{
	GENERATED_BODY()
	
public:
	UActionCard(const FObjectInitializer& ObjectInitializer);

	void SetActionType(ERpgActionType Type);
	void SetAttackTarget(CPPRpgTargetType TargetType);
	void SetAttackPower(int32 Power);

	void SetDefenceTarget(CPPRpgTargetType TargetType);
	void SetDefencePower(int32 Power);

	ERpgActionType GetActionType() const;
	CPPRpgTargetType GetAttackTarget() const;
	int32 GetAttackPower() const;

	CPPRpgTargetType GetDefenceTarget() const;
	int32 GetDefencePower() const;


protected:
	// アクションパラメーター
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<URpgActionParameter> ActionParameter;

};
