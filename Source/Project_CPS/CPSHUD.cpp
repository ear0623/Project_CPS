// Fill out your copyright notice in the Description page of Project Settings.


#include "CPSHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"


ACPSHUD::ACPSHUD()
{

	
}

void ACPSHUD::BeginPlay()
{
	if (ClassOfWidget != NULL)
	{
		ClassWidget = CreateWidget(GetWorld(), ClassOfWidget);
		ClassWidget->AddToViewport();
	}
	
}

void ACPSHUD::GetCurrentDay(UTextBlock* Day)
{
	FDateTime CurrentDateTime = FDateTime::Now();

	FString DayOfWeek = CurrentDateTime.ToString(TEXT("%A"));
	FString Date = CurrentDateTime.ToString(TEXT("%m/%d/%Y"));
	FString Time = CurrentDateTime.ToString(TEXT("%H:%M"));

	if (Day != nullptr)
	{
		FString Day_Local = DayOfWeek + "  " + Date + "  " + Time;
		Day->SetText(FText::FromString(Day_Local));
		
	}
	
}

