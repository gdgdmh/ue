// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollTestUserWidget.h"
#include "BalloonUserWidget.h"

#include "Common/DataTableUtility.h"

void UScrollTestUserWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::NativeConstruct"));
	Super::NativeConstruct();
	Set();
}

void UScrollTestUserWidget::Set()
{
	Clear();

	TObjectPtr<UDataTableUtility> util = NewObject<UDataTableUtility>();

	FString DataTableReferencePath = TEXT("/Script/Engine.DataTable'/Game/Project/UI/DataTables/DT_UITestData.DT_UITestData'");
	UDataTableUtility::LoadStatus Status = util->LoadDataTable<FScrollTestDataTable>(TestDataTables, DataTableReferencePath);
	if ((Status == UDataTableUtility::LoadStatus::Success) || (Status == UDataTableUtility::LoadStatus::FailureEmptyData))
	{
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget load failure"));
	}

#if 0
	{
		TestDataTables.Empty();
		// DataTable読み込み
		FString Path = TEXT("/Script/Engine.DataTable'/Game/Project/UI/DataTables/DT_UITestData.DT_UITestData'");
		TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *Path, nullptr, LOAD_None, nullptr);

		if (!DataTable)
		{
			UE_LOG(LogTemp, Log, TEXT("DataTable load failure"));
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("DataTable load success"));

		// データ取得
		TArray<FName> RowArray = DataTable->GetRowNames();
		for (const FName RowName : RowArray)
		{
			auto TempTable = DataTable->FindRow<FScrollTestDataTable>(RowName, FString());
			if (!TempTable)
			{
				UE_LOG(LogTemp, Log, TEXT("Row find failure(TableType?)"));
				continue;
			}
			UE_LOG(LogTemp, Log, TEXT("Row find success"));
			TestDataTables.Add(*TempTable);
		}
	}
#endif

	// 動的にボタンを追加
	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_Balloon.WBP_Balloon_C");
	TSubclassOf<class UUserWidget> TempWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!TempWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("WBP_Balloon widget load failure"));
		return;
	}

	int32 Size = TestDataTables.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		TObjectPtr<UBalloonUserWidget> Balloon = CreateWidget<UBalloonUserWidget>(GetWorld(), TempWidgetClass);
		if (Balloon)
		{
			// Viewportの追加、Subsystemへの追加
			Balloon->AddToViewport(20);
			Balloon->AddUserWidgetSubsytem();
			// スクロールBoxにも追加
			DynamicScrollBox->AddChild(Balloon);
			BalloonUserWidgets.Add(Balloon);
			// このタイミングで初期化しないとNativeConstructが呼ばれてしまうことがあるので適用されない
			Balloon->SetText(TestDataTables[i].Name);
		}
	}
}

void UScrollTestUserWidget::Clear()
{
	TestDataTables.Empty();

	// ViewportとSubsytemから削除
	int32 Size = BalloonUserWidgets.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		BalloonUserWidgets[i]->RemoveFromParent();
		BalloonUserWidgets[i]->RemoveUserWidgetSubsystem();
	}
	BalloonUserWidgets.Empty();
	

}

void UScrollTestUserWidget::OnEventUserScrolled()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::OnEventUserScrolled"));
}