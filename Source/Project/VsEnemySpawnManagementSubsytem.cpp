// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemySpawnManagementSubsytem.h"
#include "Kismet/GameplayStatics.h"
#include "GetRandomAngle.h"

UVsEnemySpawnManagementSubsytem::UVsEnemySpawnManagementSubsytem()
{
}

bool UVsEnemySpawnManagementSubsytem::ShouldCreateSubsystem(UObject* Outer) const
{
	// いったんtrueにする
	// ただ将来的には条件に応じてtrueにしないと全部のレベルで生成されるため、注意
	return true;
}

void UVsEnemySpawnManagementSubsytem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Initialize"));
	bIsActive = false;
	SpawnVsEnemy = GetWorld()->SpawnActor<ASpawnVsEnemy>();
	Start(GetWorld()->GetTimerManager());
}

void UVsEnemySpawnManagementSubsytem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Deinitialize"));
}

void UVsEnemySpawnManagementSubsytem::Start(FTimerManager& TimerManager)
{
	bIsActive = true;
	StartTimer(TimerManager);
}

void UVsEnemySpawnManagementSubsytem::StartTimer(FTimerManager& TimerManager)
{
	const float SpawnSecond = 5.0f;
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::StartTimer"));
	TimerManager.SetTimer(TimerHandle, this, &UVsEnemySpawnManagementSubsytem::OnTimerElapsed, SpawnSecond, false);
}

void UVsEnemySpawnManagementSubsytem::OnTimerElapsed()
{
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::OnTimerElapsed"));
	FVector Location(950, 300, 90);
	FRotator Rotation(0, 0, 0);

	// プレイヤーの位置情報を取得
	{
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


	StartTimer(GetWorld()->GetTimerManager());
}

void UVsEnemySpawnManagementSubsytem::GetSpawnLocation(FVector& TargetLocation, float Distance, uint16 Angle)
{
	//uint16 Angle = GetRandomAngle();
	float DigreeAngle = Angle;

	TargetLocation.X += (Distance * FMath::Cos(FMath::DegreesToRadians(DigreeAngle)));
	TargetLocation.Y += (Distance * FMath::Sin(FMath::DegreesToRadians(DigreeAngle)));
}

float UVsEnemySpawnManagementSubsytem::GetRandomAngle()
{
	::GetRandomAngle RandomAngle;
	return RandomAngle.Get();
}