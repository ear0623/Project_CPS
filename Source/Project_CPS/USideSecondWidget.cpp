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

			/*AddChildWidget = Cast<UUListWidget>(List->GetEntryWidgetClass());
			AddChildWidget = CreateWidget(this, List->GetEntryWidgetClass());
			ListAdd = dynamic_cast<UUListWidget*>(AddChildWidget);
			List->AddItem(ListAdd);*/
	}
	ID = 0;
	DataName =" ";
	DataValue = 0;
	VCID = 0;
	VCName = " ";
	Type = 0;

	
}


void UUSideSecondWidget::SetListView(int64 idmumber, FString datanamestring, int64 datavalueNumber, int64 vcidNumber, FString vcnameNumber, int64 typeNumber)
{
	DataName = datanamestring;

	//ListAdd->SetItemName();
	
	AddChildWidget = Cast<UUListWidget>(List->GetEntryWidgetClass());
	AddChildWidget = CreateWidget(this, List->GetEntryWidgetClass());
	ListAdd = dynamic_cast<UUListWidget*>(AddChildWidget);
	ItemName.Add(datanamestring);
	ListAdd->SetListName(ItemName);
	//List->SetListItems(ItemName);
	//ListAdd->UpdateListName(FText::FromString(DataName));
	List->AddItem(ListAdd);
	
	
}
