// Fill out your copyright notice in the Description page of Project Settings.


#include "CPS_GameMode.h"
#include "HTTPObject.h"

void ACPS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	DataObject = NewObject<UHTTPObject>(this);


}
