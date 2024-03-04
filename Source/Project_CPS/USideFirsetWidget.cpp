// Fill out your copyright notice in the Description page of Project Settings.


#include "USideFirsetWidget.h"
#include "Components/TreeView.h"
#include "UListWidget.h"

void UUSideFirsetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//TreeViewEquip->SetOnGetItemChildren<UListWidget>();
}

void UUSideFirsetWidget::OnGetItemChildren(UObject* pltem, TArray<UObject*>& AChildren)
{
}
