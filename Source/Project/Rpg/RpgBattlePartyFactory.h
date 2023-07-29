// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleParty.h"
#include "CPPRpgBattlePartyFactoryType.h"
#include "RpgBattlePartyFactory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattlePartyFactory : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattlePartyFactory(const FObjectInitializer& ObjectInitializer);

	TWeakObjectPtr<URpgBattleParty> Create(ERpgBattlePartyFactoryType Type);
};
