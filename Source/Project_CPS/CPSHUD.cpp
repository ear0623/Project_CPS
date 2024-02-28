// Fill out your copyright notice in the Description page of Project Settings.


#include "CPSHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"


ACPSHUD::ACPSHUD()
{

	
}

void ACPSHUD::BeginPlay()
{
	if (ClassOfWidget != NULL)
	{
		ClassWidget = Cast<UUserWidget>(ClassOfWidget);
		ClassWidget = CreateWidget(GetWorld(), ClassOfWidget);
		ClassWidget->AddToViewport();
	}
	
}

void ACPSHUD::GetCurrentDay(UTextBlock* Day)
{
	FDateTime CurrentDateTime = FDateTime::Now();

	
	FString Date = CurrentDateTime.ToString(TEXT("%m/%d/%Y"));
	FString DayOfWeek = CurrentDateTime.ToString(TEXT("%A"));
	FString Time = CurrentDateTime.ToString(TEXT("%H:%M"));

	if (Day != nullptr)
	{
		FString Day_Local =  Date + "  " + DayOfWeek + "  " + Time;
		Day->SetText(FText::FromString(Day_Local));
		
	}
	
}


