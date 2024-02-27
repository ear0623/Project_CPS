// Fill out your copyright notice in the Description page of Project Settings.


#include "APController.h"
#include "Camera/PlayerCameraManager.h"
#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
		MyPlayer->GetCamera()->SetWorldRotation(FRotator(0,0,0));
		MyPlayer->GetCamera()->SetWorldLocation(FVector(0, 0, 0));
		MyPlayer->GetSpringArm()->TargetArmLength = 150.0f;
	}
}

void AAPController::UseingTargetArm()
{
	TObjectPtr<APlayerPawn>MyPlayer = Cast<APlayerPawn>(this->GetPawn());
	if (MyPlayer != nullptr)
	{

	}
}
