// Fill out your copyright notice in the Description page of Project Settings.


#include "UListWidget.h"
#include "AStructorActor.h"
#include "UListWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UUListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AStructor = NewObject<AAStructorActor>();
}

void UUListWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	TObjectPtr<UUListWidget> ListItem = Cast<UUListWidget>(ListItemObject);
	if (ListItem != nullptr&&AStructor != nullptr)
	{
		AStructor->SetData();
		Name->SetText(FText::FromString(AStructor->GetDataTable().GetSpellName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString::Printf(TEXT("False")));
	}
}

void UUListWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
}


