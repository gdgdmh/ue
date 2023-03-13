// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVsEnemy.h"
#include "SpawnEnemyManager.generated.h"

UCLASS()
class PROJECT_API ASpawnEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float ProcessSpawn();
	void OnSpawnAfter();

private:
	// �v���C���[�̈ʒu���擾
	void GetPlayerLocation(FVector& Location);
	// �^�[�Q�b�g�̈ʒu��Distance�AAngle��n�����Ƃ�Spawn����ʒu���擾����
	void GetSpawnLocation(FVector& TargetLocation, float Distance, uint16 Angle);
	// �����_����Angle���擾
	float GetRandomAngle();


public:
	UPROPERTY()
		TObjectPtr<ASpawnVsEnemy> SpawnVsEnemy;
	float ElapsedTime;	// �o�ߎ���

};
