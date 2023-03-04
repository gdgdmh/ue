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
	// �����ł��Ȃ������Ƃ���nullptr�ɂȂ�̂Œ���
	TObjectPtr<AActor> Spawn(EEnemyType type, const FVector& Location, const FRotator& Rotation)
	{
		switch (type)
		{
		case EEnemyType::Bat:
		{
			// �p�X�͌�ق�DataTable�ȂǂŊǗ�����\��
			FString AssetPath = TEXT("/Game/Project/AI/VSEnemy/BP_VSEnemyCharacter.BP_VSEnemyCharacter_C");
			// �A�Z�b�g�ǂݍ���
			TSubclassOf<AActor> ActorClass = TSoftClassPtr<AActor>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
			FActorSpawnParameters ActorSpawnParameter;
			// AIController��Spawn���Ȃ��Ƃ���Auto PossessAI��Placed in World or Spawned�ɂȂ��Ă��邩�m�F���邱��
			// Placed in World���Ɛ�������Ȃ�
			return GetWorld()->SpawnActor<AActor>(ActorClass, Location, Rotation, ActorSpawnParameter);
		}
		// �ȉ��͖�����
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
