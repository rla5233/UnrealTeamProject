// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Title/MainTitleHUD.h"
#include "Blueprint/UserWidget.h"
//#include "Global/MainGameBlueprintFunctionLibrary.h"
//#include "Global/DataTable/WidgetDataRow.h"
#include "Global/MainGameInstance.h"

void AMainTitleHUD::BeginPlay()
{
	Super::BeginPlay();

	AllUISetting();
}

void AMainTitleHUD::AllUISetting()
{
	Super::AllUISetting();


	TMap<FString, FWidgetDataRow>& AllUI = Inst->GetTitleWidgets();
	UEnum* Enum = StaticEnum<EUserWidgetType>();

	for (TPair<FString, FWidgetDataRow> Pair : AllUI)
	{
		FWidgetDataRow& Data = Pair.Value;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Data.GetWidget());
		Widget->AddToViewport();

		EUserWidgetType Type = static_cast<EUserWidgetType>(Enum->GetValueByName(*Pair.Key));

		AllWidgets.Add(Type, Widget);

		if (true == Data.GetStartOn())
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}
		else if (false == Data.GetStartOn())
		{
			Widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}