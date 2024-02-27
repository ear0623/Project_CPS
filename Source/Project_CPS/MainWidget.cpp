// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "UOptionWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Option_Button->OnClicked.AddDynamic(this, &UMainWidget::SetBlind);
	
}

void UMainWidget::SetBlind()
{
	OptionBox->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp,Warning,TEXT("SetBlind"))
}
