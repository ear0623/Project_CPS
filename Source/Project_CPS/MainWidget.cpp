// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "UOptionWidget.h"
#include "UPopUpWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Option_Button->OnClicked.AddDynamic(this, &UMainWidget::SetBlind);
	Exit->OnClicked.AddDynamic(this, &UMainWidget::SetPopUpWidget_Exit);
}

void UMainWidget::SetBlind()
{
	OptionBox->SetVisibility(ESlateVisibility::Visible);
	PopUp->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::SetPopUpWidget_Exit()
{
	OptionBox->SetVisibility(ESlateVisibility::Collapsed);
	PopUp->SetVIsible(ESlateVisibility::Visible,0);
}
