// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemySpawnManagementSubsytem.h"

UVsEnemySpawnManagementSubsytem::UVsEnemySpawnManagementSubsytem()
{
}

bool UVsEnemySpawnManagementSubsytem::ShouldCreateSubsystem(UObject* Outer) const
{
	// ��������true�ɂ���
	// ���������I�ɂ͏����ɉ�����true�ɂ��Ȃ��ƑS���̃��x���Ő�������邽�߁A����
	return true;
}

void UVsEnemySpawnManagementSubsytem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Initialize"));
}

void UVsEnemySpawnManagementSubsytem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Deinitialize"));
}
