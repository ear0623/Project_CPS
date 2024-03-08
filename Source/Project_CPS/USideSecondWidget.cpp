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

	
	if (List->GetEntryWidgetClass() != NULL)
	{
		AddChildWidget = NewObject<UUListWidget>(this, List->GetEntryWidgetClass());
		/*AddChildWidget = Cast<UUListWidget>(List->GetEntryWidgetClass());*/
		
		ListAdd = dynamic_cast<UUListWidget*>(AddChildWidget);
		
		for (const auto& Items : ItemName)
		{
			AddChildWidget = CreateWidget(this, List->GetEntryWidgetClass()); 
			ListAdd->SetName(FText::FromString(Items));
			List->AddItem(ListAdd);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, Items);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("XXTTXX")));
		}

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("TTXXTT")));
	}
	ID = 0;
	DataName =" ";
	DataValue = 0;
	VCID = 0;
	VCName = " ";
	Type = 0;
}


void UUSideSecondWidget::SetListView(int64 idnumber, FString datanamestring, int64 datavalueNumber, int64 vcidNumber, FString vcnameNumber, int64 typeNumber)
{
	DataName = datanamestring;

	ListAdd->SetListView_ListWidget(idnumber, datanamestring, datavalueNumber, vcidNumber, vcnameNumber, typeNumber);

}
