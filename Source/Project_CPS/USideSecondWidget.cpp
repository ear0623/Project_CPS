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

	if (ClassOfWidget != NULL)
	{
		AddChildWidget = Cast<UUListWidget>(ClassOfWidget);
		AddChildWidget = CreateWidget(this, ClassOfWidget);
		
		//ListAdd = dynamic_cast<UUListWidget*>(AddChildWidget);
	}
	ID = 0;
	DataName =" ";
	DataValue = 0;
	VCID = 0;
	VCName = " ";
	Type = 0;
}


void UUSideSecondWidget::SetListView(int64 idmumber, FString datanamestring, int64 datavalueNumber, int64 vcidNumber, FString vcnameNumber, int64 typeNumber, UUListWidget ClassListWidget)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("ConnectSetList")));
	DataName = datanamestring;
	List->AddItem()
}
