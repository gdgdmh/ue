// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollTestUserWidget.h"
#include "BalloonUserWidget.h"

void UScrollTestUserWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::NativeConstruct"));
	Super::NativeConstruct();
	Set();
}

void UScrollTestUserWidget::Set()
{
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

			Balloon->AddToViewport(20);
			Balloon->AddUserWidgetSubsytem();
			DynamicScrollBox->AddChild(Balloon);
			// このタイミングで初期化しないとNativeConstructが呼ばれてしまうことがあるので適用されない
			Balloon->SetText(TestDataTables[i].Name);
		}
	}



#if 0
	// 動的にボタンを追加
	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_Balloon.WBP_Balloon_C");
	TSubclassOf<class UUserWidget> TempWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!TempWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("WBP_Balloon widget load failure"));
		return;
	}

	TObjectPtr<UBalloonUserWidget> Balloon = CreateWidget<UBalloonUserWidget>(GetWorld(), TempWidgetClass);
	if (Balloon)
	{
		
		Balloon->AddToViewport(20);
		Balloon->AddUserWidgetSubsytem();
		DynamicScrollBox->AddChild(Balloon);
		// このタイミングで初期化しないとNativeConstructが呼ばれてしまうことがあるので適用されない
		Balloon->SetData();
	}
#endif
}

void UScrollTestUserWidget::OnEventUserScrolled()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::OnEventUserScrolled"));
}