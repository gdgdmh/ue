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
	void SetFirstTimer(float Timer);
	float GetNextTimer() const { return NextTimer; }

	float ProcessSpawn();
	void OnSpawnAfter();

private:
	float SpawnPhase1();
	float SpawnPhase2();
	float SpawnPhase3();


private:
	// プレイヤーの位置を取得
	void GetPlayerLocation(FVector& Location);
	// ターゲットの位置とDistance、Angleを渡すことでSpawnする位置を取得する
	void GetSpawnLocation(FVector& TargetLocation, float Distance, uint16 Angle);
	// ランダムなAngleを取得
	float GetRandomAngle();


public:
	UPROPERTY()
		TObjectPtr<ASpawnVsEnemy> SpawnVsEnemy;
	float ElapsedTime;	// 経過時間
	float NextTimer;	// 次のタイマーに設定する時間

};
