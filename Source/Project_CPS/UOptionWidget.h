// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UOptionWidget.generated.h"

class UBorder;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_CPS_API UUOptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBorder> BorderSize;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Option;

protected:

public:

};
