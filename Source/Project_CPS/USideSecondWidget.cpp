// Fill out your copyright notice in the Description page of Project Settings.


#include "USideSecondWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "AStructorActor.h"
#include "HTTPObject.h"
#include "Components/ListView.h"
#include "UListWidget.h"
#include "HTTPActor.h"


void UUSideSecondWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Background = Cast<UBorder>(GetWidgetFromName(TEXT("Background")));
	Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text")));

	

}


void UUSideSecondWidget::SetListVuew(int64 Id, FString DataName, int64 DataValue, int64 VCID, FString VCName, int64 Type)
{
	
	if(List->GetEntryWidgetClass())
	{
		UUListWidget* SaveWidget = CreateWidget<UUListWidget>(this, List->GetEntryWidgetClass());
		if (SaveWidget)
		{
			SaveWidget->GetItemName()->SetText(FText::FromString(DataName));
			List->AddItem(SaveWidget);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, DataName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, DataName);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, DataName);
}

