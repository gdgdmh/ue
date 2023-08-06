// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPPSideType.h"
#include "RpgBattleCharacterBase.h"
#include "RpgBattleCharacterParameter.h"
#include "CharacterParameterConverter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UCharacterParameterConverter : public UObject
{
	GENERATED_BODY()
	
public:
	TWeakObjectPtr<URpgBattleCharacterBase> Convert(const URpgBattleCharacterParameter& Parameter, ESideType SideType);
};
