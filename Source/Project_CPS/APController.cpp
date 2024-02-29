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
	Location = { 0.0, 0.0, 0.0 };
}

void AAPController::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> LocalPlayersubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalPlayersubSystem)
	{
		LocalPlayersubSystem->AddMappingContext(MappingContext, 0);
	}
	MyPlayer = Cast<APlayerPawn>(this->GetPawn());
}

void AAPController::InitSetting()
{
	if (MyPlayer != nullptr)
	{
		GetWorldTimerManager().SetTimer(TimerHandle,this, &AAPController::InitSetting_Camera, 0.01f, true);
	}
}

void AAPController::InitSetting_Camera()
{
	float InterSpeed = 0.1f;
	float DeltaTime = FApp::GetDeltaTime();
	FRotator CurrentRotator = MyPlayer->GetSpringArm()->GetRelativeRotation();
	FRotator ObjectRotator = { 0.0f, 0.0f, 0.0f };
	FRotator TargetRotator = ObjectRotator;
	FRotator InterpRotation = FMath::RInterpTo(CurrentRotator, TargetRotator, DeltaTime, InterSpeed);
	MyPlayer->GetSpringArm()->SetWorldRotation(InterpRotation);

	float InterSpeed_Arm = 0.1f;
	float Currentfloat = MyPlayer->GetSpringArm()->TargetArmLength;
	float Targetfloat = 300;
	float Interpfloat = FMath::FInterpTo(Currentfloat, Targetfloat, DeltaTime, InterSpeed_Arm);
	MyPlayer->GetSpringArm()->TargetArmLength = Interpfloat;

	if (FMath::IsNearlyEqual(InterpRotation.Yaw, TargetRotator.Yaw, 1.0f)&& Currentfloat == 300)
	{
		MyPlayer->GetSpringArm()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
		MyPlayer->GetSpringArm()->TargetArmLength = 300.0f;
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AAPController::InitSetting_Camera_Location()
{
	float InterSpeed = 0.1f; 
	float DeltaTime = FApp::GetDeltaTime(); 
	FVector CurrentVector = MyPlayer->GetSpringArm()->GetRelativeLocation(); 
	FVector TargetVector = Location;
	FVector InterpVector = FMath::VInterpTo(CurrentVector, TargetVector, DeltaTime, InterSpeed);
	MyPlayer->GetSpringArm()->SetWorldLocation(InterpVector);

	if (FMath::IsNearlyEqual(CurrentVector.X, TargetVector.X, 1.0f)&&FMath::IsNearlyEqual(CurrentVector.Y, TargetVector.Y, 1.0f)&&FMath::IsNearlyEqual(CurrentVector.Z, TargetVector.Z, 1.0f))
	{
		MyPlayer->GetSpringArm()->SetWorldLocation(TargetVector);
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AAPController::InitSetting_SprinArm()
{
	float InterSpeed = 5.1f;
	float DeltaTime = FApp::GetDeltaTime(); 
	float Currentfloat = MyPlayer->GetSpringArm()->TargetArmLength;
	float Targetfloat = 300;
	float Interpfloat = FMath::FInterpTo(Currentfloat, Targetfloat, DeltaTime, InterSpeed);
	MyPlayer->GetSpringArm()->TargetArmLength = Interpfloat;

	if (FMath::IsNearlyEqual(Currentfloat, Targetfloat, 1.0f))
	{
		MyPlayer->GetSpringArm()->TargetArmLength = 300.0f;
		GetWorldTimerManager().ClearTimer(TimerHandle_Arm);
	}
}


bool AAPController::GetHit()
{
	FHitResult Hitresult;
	bool ClickValue = this->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, Hitresult);
	if (ClickValue)
	{
		FName Type="Type01";
		if (Hitresult.GetActor()->ActorHasTag(Type))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString::Printf(TEXT("True")));
			Location = Hitresult.GetActor()->GetActorLocation()+Hitresult.ImpactNormal*300;
			FRotator Rotation = Hitresult.GetActor()->GetActorRotation();

			//GetWorldTimerManager().SetTimer(TimerHandle, this, &AAPController::InitSetting_Camera_Location, 0.01f, true);
		}
	}

	return ClickValue;
}


