// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyActionParameter.h"

//#include "Math\RandomStream.h"

#include "../../Common/DataTableUtility.h"

const FName UEnemyActionParameter::LightAttackName = TEXT("LightAttack");
const FName UEnemyActionParameter::LightDefenceName = TEXT("LightDefence");

UEnemyActionParameter::UEnemyActionParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ActionDataTables()
	, LightAttackIndex(-1)
	, LightDefenceIndex(-1)
{
}

bool UEnemyActionParameter::LoadDataTable(const FString& DataTableReferencePath)
{

	ActionDataTables.Empty();
	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable load failure"));
		return false;
	}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable DataTable empty"));
		return true;
	}

	int32 index = 0;
	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FEnemyActionDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable Row find failure(TableType?)"));
			continue;
		}

		if (LightAttackName == RowName)
		{
			// 名前が一致したらindexをとっておく
			LightAttackIndex = index;
		}
		else if (LightDefenceName == RowName)
		{
			LightDefenceIndex = index;
		}

		ActionDataTables.Add(*TempTable);
		++index;
	}

	if (ActionDataTables.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable DataTable add failure(empty)"));
		return false;
	}
	if (LightAttackIndex < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable LightAttackIndex Not Found"));
	}
	if (LightDefenceIndex < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable LightDefenceIndex Not Found"));
	}
	return true;
}

void UEnemyActionParameter::Test()
{

// 間違い
#if 0
	const int32 Size = 5;
	for (int32 i = 0; i < Size; ++i)
	{
		FEnemyAndEnemyActionDataTable Table;
		GetRandomEnemyActionData(Table, ECdEnemyType::Slime);

		if (Table.EnemyType == ECdEnemyType::Slime)
		{

		}

	}
#endif // if 0

#if 0
	FRandomStream r(0);
	r.GenerateNewSeed();

	{
		int32 result = r.RandRange(0, 100);
		int32 result2 = r.RandRange(0, 100);
		float result3 = r.GetFraction();

		int32 a = 0;
		a = 10;
		int32 seed = r.GetInitialSeed();
		seed = 10;

	}
#endif

}

const FEnemyActionDataTable& UEnemyActionParameter::Get(int32 index) const
{
	return ActionDataTables[index];
}

const FEnemyActionDataTable& UEnemyActionParameter::GetSimpleAttack() const
{
	checkf(LightAttackIndex >= 0, TEXT("UEnemyActionParameter::GetSimpleAttack Invalid"));
	return ActionDataTables[LightAttackIndex];
}

const FEnemyActionDataTable& UEnemyActionParameter::GetSimpleDefence() const
{
	checkf(LightDefenceIndex >= 0, TEXT("UEnemyActionParameter::GetSimpleDefence Invalid"));
	return ActionDataTables[LightDefenceIndex];
}


int32 UEnemyActionParameter::Size() const
{
	return ActionDataTables.Num();
}

UEnemyAndEnemyActionDataParameter::UEnemyAndEnemyActionDataParameter(const FObjectInitializer& ObjectInitializer)
	: EnemyAndEnemyActionDataTables()
{

}

bool UEnemyAndEnemyActionDataParameter::LoadDataTable(const FString& DataTableReferencePath)
{
	TObjectPtr<UDataTableUtility> TableUtil = NewObject<UDataTableUtility>();

	EnemyAndEnemyActionDataTables.Empty();
	UDataTableUtility::LoadStatus Status = TableUtil->LoadDataTable<FEnemyAndEnemyActionDataTables>(EnemyAndEnemyActionDataTables, DataTableReferencePath);
	switch (Status)
	{
	case UDataTableUtility::LoadStatus::Success:
		return true;
	case UDataTableUtility::LoadStatus::FailureEmptyData:
		return true;
	default:
		return false;
	}
	return false;
}

int32 UEnemyAndEnemyActionDataParameter::Size() const
{
	return EnemyAndEnemyActionDataTables.Num();
}

// 特定の敵の行動データを取得する
bool UEnemyAndEnemyActionDataParameter::GetEnemyActionData(TArray<FEnemyAndEnemyActionDataTable>& Tables, ECdEnemyType Type) const
{
	Tables.Empty();
	for (const auto& Table : EnemyAndEnemyActionDataTables)
	{
		for (const FEnemyAndEnemyActionDataTable& Data : Table.EnemyAndEnemyActionDatas)
		{
			if (Type == Data.EnemyType)
			{
				Tables.Add(Data);
			}
		}
	}

	if (Tables.IsEmpty())
	{
		return false;
	}
	return true;
}

bool UEnemyAndEnemyActionDataParameter::GetRandomEnemyActionData(FEnemyAndEnemyActionDataTable& Table, ECdEnemyType Type)
{
	// 念のためにクリアしておく
	Table.EnemyActionDatas.Empty();

	TArray<FEnemyAndEnemyActionDataTable> EnemyTables;
	GetEnemyActionData(EnemyTables, Type);
	if (EnemyTables.IsEmpty())
	{
		// データがない
		return false;
	}

	int32 num = EnemyTables.Num();
	if (num == 1)
	{
		int32 tableIndex = 0;
		// 1つの場合
		for (const auto& ActionData : EnemyTables[tableIndex].EnemyActionDatas)
		{
			Table.EnemyActionDatas.Add(ActionData);
		}
		return true;
	}

	int32 tableIndex = GetRandomInt(0, num - 1);

	auto& RandomEnemyTable = EnemyTables[tableIndex];
	for (const auto& ActionData : RandomEnemyTable.EnemyActionDatas)
	{
		Table.EnemyActionDatas.Add(ActionData);
	}
	return true;
}

int32 UEnemyAndEnemyActionDataParameter::GetRandomInt(int32 Min, int32 Max)
{
	FRandomStream r(0);
	r.GenerateNewSeed();
	return r.RandRange(Min, Max);
}

void UEnemyAndEnemyActionDataParameter::Test()
{
	const int32 Size = 3;
	for (int32 i = 0; i < Size; ++i)
	{
		FEnemyAndEnemyActionDataTable Table;
		GetRandomEnemyActionData(Table, ECdEnemyType::Slime);
		if (Table.EnemyType == ECdEnemyType::Slime)
		{
			Table.EnemyType = ECdEnemyType::None;
		}
	}

}
