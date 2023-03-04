// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPEnemyType.h"
#include "SpawnVsEnemy.generated.h"

UCLASS()
class PROJECT_API ASpawnVsEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVsEnemy() { PrimaryActorTick.bCanEverTick = false; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override { Super::BeginPlay(); }

public:	
	// 生成できなかったときはnullptrになるので注意
	TObjectPtr<AActor> Spawn(EEnemyType type, const FVector& Location, const FRotator& Rotation)
	{
		switch (type)
		{
		case EEnemyType::Bat:
		{
			// パスは後ほどDataTableなどで管理する予定
			FString AssetPath = TEXT("/Game/Project/AI/VSEnemy/BP_VSEnemyCharacter.BP_VSEnemyCharacter_C");
			// アセット読み込み
			TSubclassOf<AActor> ActorClass = TSoftClassPtr<AActor>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
			FActorSpawnParameters ActorSpawnParameter;
			// AIControllerがSpawnしないときはAuto PossessAIがPlaced in World or Spawnedになっているか確認すること
			// Placed in Worldだと生成されない
			return GetWorld()->SpawnActor<AActor>(ActorClass, Location, Rotation, ActorSpawnParameter);
		}
		// 以下は未実装
		case EEnemyType::Skeleton:
			return nullptr;
		case EEnemyType::Num:
			return nullptr;
		default:
			return nullptr;
		}
		return nullptr;
	}
};
