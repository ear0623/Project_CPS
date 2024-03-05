// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "USideSecondWidget.generated.h"

class UBorder;
class UTextBlock;
class UListView;
class UHTTPObject;
class AHTTPActor;
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HTTP", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHTTPObject> DataObject;

public:

	UFUNCTION(BlueprintCallable)
	void SetListVuew(int64 Id, FString DataName, int64 DataValue, int64 VCID, FString VCName, int64 Type);


};
