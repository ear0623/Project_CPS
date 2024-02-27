// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPSHUD.generated.h"

class UUserWidget;
class UTextBlock;
/**
 * 
 */

UCLASS()
class PROJECT_CPS_API ACPSHUD : public AHUD
{
	GENERATED_BODY()
	
	ACPSHUD();

private:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> ClassWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ClassOfWidget;


public:
	UFUNCTION(BlueprintCallable)
	void GetCurrentDay(UTextBlock* Day);
};
