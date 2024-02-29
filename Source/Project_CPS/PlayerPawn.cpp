// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "APController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Targetmesh"));
	TargetMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
	SpringArm->SetupAttachment(TargetMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	TObjectPtr<UEnhancedInputComponent> Enhanced = Cast< UEnhancedInputComponent>(PlayerInputComponent);
	if(IsValid(Enhanced))
	{
		Enhanced->BindAction(IA_Wheel, ETriggerEvent::Triggered, this, &APlayerPawn::ZoomInOut);
		Enhanced->BindAction(IA_Rotater, ETriggerEvent::Triggered, this, &APlayerPawn::RotatorValue);
		Enhanced->BindAction(IA_MouseAxisX, ETriggerEvent::Triggered, this, &APlayerPawn::RotatorValue);
		Enhanced->BindAction(IA_Click, ETriggerEvent::Started, this, &APlayerPawn::OnClik);
	}

}

void APlayerPawn::ZoomInOut(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	float Length = GetSpringArm()->TargetArmLength;
	Length += (InputValue*10);
	//UE_LOG(LogTemp, Warning, TEXT("zoominout"));
	GetSpringArm()->TargetArmLength = Length;
}

void APlayerPawn::RotatorValue(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	FRotator ArmRotatorValue = GetSpringArm()->GetRelativeRotation();
	ArmRotatorValue.Yaw += (10 * InputValue);
	GetSpringArm()->SetRelativeRotation(ArmRotatorValue);
}

void APlayerPawn::OnClik(const FInputActionValue& Value)
{
	bool InputValue = Value.Get<bool>();
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString::Printf(TEXT("Value : %s"), InputValue ? TEXT("true") : TEXT("false")));

	TObjectPtr<AAPController> AAPcontroller = Cast<AAPController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (AAPcontroller)
	{
		AAPcontroller->GetHit();
	}

}

