// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UListWidget.generated.h"

class UTextBlock;
class UButton;
class AAStructorActor;
/**
 * 
 */
UCLASS()
class PROJECT_CPS_API UUListWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Name;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> NameButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Count;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AAStructorActor> AStructor;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	FText ListName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TArray<FString> ItemName; 

public:
	TObjectPtr<UTextBlock> GetItemName() { return Name.Get(); }

	void SetItemName();

	FText GetListName() { return ListName; }
	void SetListName(TArray<FString> Itemname);

	TObjectPtr<UTextBlock> GetCount() { return Count.Get(); }
public:
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	void UpdateListName(FText name);

	
	
};
