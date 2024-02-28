// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROJECT_CPS_API AAPController : public APlayerController
{
	GENERATED_BODY()
	
	AAPController();
private:

public:
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced",meta= (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

public:
	UFUNCTION(BlueprintCallable)
	void InitSetting();

};
