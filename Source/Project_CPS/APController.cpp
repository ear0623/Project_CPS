// Fill out your copyright notice in the Description page of Project Settings.


#include "APController.h"
#include "Camera/PlayerCameraManager.h"
#include "PlayerPawn.h"

AAPController::AAPController()
{

	
}

void AAPController::BeginPlay()
{

}

void AAPController::InitSetting()
{
	TObjectPtr<APlayerPawn>MyPlayer = Cast<APlayerPawn>(this->GetPawn());
	if (MyPlayer != nullptr)
	{
		MyPlayer->GetCamera();
	}
}
