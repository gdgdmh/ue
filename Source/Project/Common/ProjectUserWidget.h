// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "CPPVsUserWidgetType.h"
#include "ProjectUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UProjectUserWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	void AddUserWidgetSubsytem();

	UFUNCTION(BlueprintCallable)
	void RemoveUserWidgetSubsystem();

	void SetId(int32 id) { Id = id; }
	int32 GetId() const { return Id; }

	//void SetWidgetType(EVsUserWidgetType Type) { VsUserWidgetType = Type; }
	//EVsUserWidgetType GetWidgetType() const { return VsUserWidgetType; }

	/// <summary>
	/// オブジェクトの表示
	/// </summary>
	void ShowObject();

	/// <summary>
	/// オブジェクトの非表示
	/// </summary>
	void HideObject();

	/// <summary>
	/// オブジェクトが表示されているか
	/// </summary>
	/// <returns>trueなら表示されている</returns>
	bool IsShowing() const;

private:
	UPROPERTY()
	int32 Id = 0;
};
