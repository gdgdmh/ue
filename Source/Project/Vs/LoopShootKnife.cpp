// Fill out your copyright notice in the Description page of Project Settings.

#include "LoopShootKnife.h"
#include "WeaponKnife.h"

ALoopShootKnifer::ALoopShootKnifer()
{
}

ALoopShootKnifer::ALoopShootKnifer(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ALoopShootKnifer::~ALoopShootKnifer()
{
}

// 発射処理
void ALoopShootKnifer::ProcessShoot()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("ALoopShootKnifer::ProcessShoot Failure"));
		return;
	}
	AWeaponKnife* spawnedProjectile = World->SpawnActor<AWeaponKnife>(ShootParameter->GetLocation(), ShootParameter->GetRotation(), ShootParameter->GetSpawnParameters());
}

#if 0
void ALoopShootKnifer::BindBeforeShootDelegate(TDelegate<void()> Func)
{
	//TBaseStaticDelegateInstance 

	//template <typename... VarTypes>
	//TBaseStaticDelegateInstance<FuncType, UserPolicy, VarTypes...>::FFuncPtr InFunc;
/*
	template <typename... VarTypes>
	inline void BindStatic(typename TBaseStaticDelegateInstance<FuncType, UserPolicy, VarTypes...>::FFuncPtr InFunc, VarTypes... Vars)
	{
		*this = CreateStatic(InFunc, Vars...);
	}

*/

	BeforeShootDelegate.BindUObject(this, &ALoopShootKnifer::test);

	//BeforeShootDelegate.BindUObject(this, &Func);

	//BeforeShootDelegate.BindUFunction(this, &ALoopShootKnifer::test);
}
#endif