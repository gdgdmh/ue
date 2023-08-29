// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"
#include "CPPCdEnemyType.h"
#include "CdCharacterBase.h"

#include "CdCharacterParameter.generated.h"




/**
 *
 */
USTRUCT(BlueprintType)
struct FCdCharacterDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCdCharacterDataTable()
	{
		Hp = 1;
		MaxHp = 0;
		AttackPower = 0;
		DefencePower = 0;
		EnemyType = ECdEnemyType::None;
	}

	int32 GetHp() const { return Hp; }
	int32 GetMaxHp() const { return MaxHp; }
	int32 GetAttackPower() const { return AttackPower; }
	int32 GetDefencePower() const { return DefencePower; }
	ECdEnemyType GetEnemyType() const { return EnemyType; }

	//void SetParameter(UCdCharacterBase& Characater);

public:
	// ���݂�HP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Hp;
	// �ő�HP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxHp;
	// �U��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 AttackPower;

	// �h��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 DefencePower;

	// �G�̃^�C�v(�v���C���[��ݒ肷��Ƃ���None)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ECdEnemyType EnemyType;
};

/**
 * 
 */
UCLASS()
class PROJECT_API UCdCharacterParameter : public UObject
{
	GENERATED_BODY()
	
public:
	UCdCharacterParameter(const FObjectInitializer& ObjectInitializer);

	bool LoadPlayerDataTable(const FString& DataTableReferencePath);
	bool LoadEnemyDataTable(const FString& DataTableReferencePath);

	void GetPlayer(TArray<TObjectPtr<UCdCharacterBase> >& Player) const;
	void GetEnemy(TArray<TObjectPtr<UCdCharacterBase> >& Enemies) const;

protected:
	TArray<FCdCharacterDataTable> PlayerData;
	TArray<FCdCharacterDataTable> EnemyData;


	// /Script/Engine.DataTable'/Game/Project/UI/DataTables/Rpg/Main/DT_EnemyData.DT_EnemyData'
	// /Script/Engine.DataTable'/Game/Project/UI/DataTables/Rpg/Main/DT_PlayerData.DT_PlayerData'
};
