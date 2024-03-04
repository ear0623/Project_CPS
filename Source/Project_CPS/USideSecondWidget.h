// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "USideSecondWidget.generated.h"

class UBorder;
class UTextBlock;
class UListView;
/**
 * 
 */
UCLASS()
class PROJECT_CPS_API UUSideSecondWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	virtual void NativeConstruct() override;



private:
	UPROPERTY()
	TObjectPtr<UBorder> Background;

	UPROPERTY()
	TObjectPtr<UTextBlock> Text;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UListView> List;

	UFUNCTION(BlueprintCallable)
	void SetListVuew();


};
