// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemyManager.h"
#include "Kismet/GameplayStatics.h"
#include "GetRandomAngle.h"

// Sets default values
ASpawnEnemyManager::ASpawnEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnVsEnemy = GetWorld()->SpawnActor<ASpawnVsEnemy>();
	ElapsedTime = 0.0f;
}

float ASpawnEnemyManager::ProcessSpawn()
{
	// 経過時間によって変わる
	if (ElapsedTime < 30.0f)
	{
		SpawnPhase1();
	}
	else if (ElapsedTime < 60.0f)
	{
		SpawnPhase2();
	}
	else
	{
		SpawnPhase3();
	}

	ElapsedTime += 5.0f;
	return 5.0f;
}

void ASpawnEnemyManager::OnSpawnAfter()
{
}

// 1体だけ出現
void ASpawnEnemyManager::SpawnPhase1()
{
	FVector Location(950, 300, 90);
	FRotator Rotation(0, 0, 0);

	// プレイヤーの位置情報を取得
	GetPlayerLocation(Location);

	float Distance = 200.0f;
	uint16 Angle = GetRandomAngle();
	FVector BaseLocation = Location;
	{
		FVector LocationCenter = BaseLocation;
		GetSpawnLocation(LocationCenter, Distance, Angle);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationCenter, Rotation);
	}
}

// 3体出現
void ASpawnEnemyManager::SpawnPhase2()
{
	FVector Location(950, 300, 90);
	FRotator Rotation(0, 0, 0);

	// プレイヤーの位置情報を取得
	GetPlayerLocation(Location);

	float Distance = 200.0f;
	uint16 Angle = GetRandomAngle();
	FVector BaseLocation = Location;
	{
		FVector LocationCenter = BaseLocation;
		GetSpawnLocation(LocationCenter, Distance, Angle);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationCenter, Rotation);
	}
	{
		FVector LocationLeft = BaseLocation;
		GetSpawnLocation(LocationLeft, Distance, Angle - 20);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationLeft, Rotation);
	}
	{
		FVector LocationRight = BaseLocation;
		GetSpawnLocation(LocationRight, Distance, Angle + 20);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationRight, Rotation);
	}
}

void ASpawnEnemyManager::SpawnPhase3()
{
	FVector Location(950, 300, 90);
	FRotator Rotation(0, 0, 0);

	// プレイヤーの位置情報を取得
	GetPlayerLocation(Location);

	float Distance = 200.0f;
	uint16 Angle = GetRandomAngle();
	FVector BaseLocation = Location;
	{
		FVector LocationCenter = BaseLocation;
		GetSpawnLocation(LocationCenter, Distance, Angle);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationCenter, Rotation);
	}
	{
		FVector LocationLeft = BaseLocation;
		GetSpawnLocation(LocationLeft, Distance, Angle - 20);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationLeft, Rotation);
	}
	{
		FVector LocationRight = BaseLocation;
		GetSpawnLocation(LocationRight, Distance, Angle + 20);
		// spawn
		SpawnVsEnemy->Spawn(EEnemyType::Bat, LocationRight, Rotation);
	}

}

void ASpawnEnemyManager::GetPlayerLocation(FVector& Location)
{
	// プレイヤーの位置情報を取得
	TArray<AActor*> FoundActors;
	TSubclassOf<AActor> PlayerActor = TSoftClassPtr<AActor>(FSoftObjectPath(TEXT("/Game/Project/Player/BP_VsPlayerCharacter.BP_VsPlayerCharacter_C"))).LoadSynchronous();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerActor, FoundActors);
	for (auto Actor : FoundActors)
	{
		AActor* AnyActor = Cast<AActor>(Actor);
		if (AnyActor)
		{
			Location = AnyActor->GetActorLocation();
		}
	}
}

void ASpawnEnemyManager::GetSpawnLocation(FVector& TargetLocation, float Distance, uint16 Angle)
{
	float DigreeAngle = Angle;

	TargetLocation.X += (Distance * FMath::Cos(FMath::DegreesToRadians(DigreeAngle)));
	TargetLocation.Y += (Distance * FMath::Sin(FMath::DegreesToRadians(DigreeAngle)));
}

float ASpawnEnemyManager::GetRandomAngle()
{
	::GetRandomAngle RandomAngle;
	return RandomAngle.Get();
}
