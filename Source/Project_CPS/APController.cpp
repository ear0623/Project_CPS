// Fill out your copyright notice in the Description page of Project Settings.


#include "APController.h"
#include "Camera/PlayerCameraManager.h"
#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

AAPController::AAPController()
{
	MappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("Mappingcontext"));

	
}

void AAPController::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> LocalPlayersubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalPlayersubSystem)
	{
		LocalPlayersubSystem->AddMappingContext(MappingContext, 0);
	}
}

void AAPController::InitSetting()
{
	TObjectPtr<APlayerPawn>MyPlayer = Cast<APlayerPawn>(this->GetPawn());
	if (MyPlayer != nullptr)
	{
		MyPlayer->GetSpringArm()->SetWorldRotation(FRotator(-45.0f, 0.0f,0.0f ));
		MyPlayer->GetSpringArm()->SetWorldLocation(FVector(-690.0f, 20.0f, 590.0f));
		MyPlayer->GetSpringArm()->TargetArmLength = 300.0f;
	}
}

