// Fill out your copyright notice in the Description page of Project Settings.


#include "MngGameMode.h"

AMngGameMode::AMngGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APawn::StaticClass();
}

void AMngGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("AMngGameMode::BeginPlay"));
	Super::BeginPlay();
}
