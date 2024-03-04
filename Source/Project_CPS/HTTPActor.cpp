// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPActor.h"

// Sets default values
AHTTPActor::AHTTPActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHTTPActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHTTPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

