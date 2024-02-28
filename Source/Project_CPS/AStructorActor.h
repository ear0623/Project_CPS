// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStructorActor.generated.h"

USTRUCT(BlueprintType)
struct FSampleStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSampleStruct():rowname(1),SpellName(" "), Description(" "), Level(1), isEndItem(0) {}
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 rowname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SpellName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 isEndItem;
};

UCLASS()
class PROJECT_CPS_API AAStructorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStructorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FSampleStruct DataTable;
};
