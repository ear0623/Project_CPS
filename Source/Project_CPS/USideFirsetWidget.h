// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USideFirsetWidget.generated.h"

class UTreeView;
/**
 * 
 */
UCLASS()
class PROJECT_CPS_API UUSideFirsetWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	virtual void NativeConstruct() override;

private:
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTreeView> TreeViewEquip;

public:
	UFUNCTION()
	void OnGetItemChildren(UObject* pltem, TArray<UObject*>& AChildren);
};
