// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartyDataTableLoader.h"

#include "../Common/DataTableUtility.h"

bool UBattlePartyDataTableLoader::Load(const FString& DataTableReferencePath, TArray<FBattlePartyDataTable>& Output)
{
	TObjectPtr<UDataTableUtility> util = NewObject<UDataTableUtility>();

	UDataTableUtility::LoadStatus Status = util->LoadDataTable<FBattlePartyDataTable>(Output, DataTableReferencePath);
	if ((Status == UDataTableUtility::LoadStatus::Success) || (Status == UDataTableUtility::LoadStatus::FailureEmptyData))
	{
		return true;
	}
	return false;
}