// Fill out your copyright notice in the Description page of Project Settings.


#include "UListWidget.h"
#include "AStructorActor.h"
#include "UListWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UUListWidget::SetItemName()
{
}

void UUListWidget::SetListName(TArray<FString> Itemname)
{
	//ListName = ItemName.begin();
	//Name->SetText(ListName);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,ListName.ToString());
	ItemName = Itemname;
}

void UUListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Name->SetText(ListName);
	if (ItemName.Num() > 0)
	{
		ListName = FText::FromString(ItemName[1]);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("True")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("False")));
	}
	
	ListName = FText::FromString("InCode ");	

}

void UUListWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	Name->SetText(ListName);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, ListName.ToString());
	
}

void UUListWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{

}

void UUListWidget::UpdateListName(FText name)
{
	//ItemName.Add(name);
	//SetListName(ItemName);
	if (ItemName.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("ItemName contains %d elements"), ItemName.Num()));
		// 다른 처리를 수행하거나 ItemName 배열의 요소를 출력하려면 여기에 추가합니다.
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("ItemName is empty"));
	}
	ListName = name;
}


