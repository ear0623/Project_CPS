// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HTTPObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpConnectStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpConnectProcessDelegate, int32, RecvSize, int32, TotalSize, float, Percent); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHttpConnectFinishedDelegate, bool, bIsSuccess, FString, ContentPath);


/**
 * 
 */
UCLASS()
class PROJECT_CPS_API UHTTPObject : public UObject
{
	GENERATED_BODY()
	
public:
	UHTTPObject();

	UFUNCTION(BlueprintCallable,Category = "HTTP", DisplayName = "HttpConnect")
	void ExcuteHttp(FString SourceURL, FString Path, FString Name);

	UPROPERTY(BlueprintAssignable)
	FHttpConnectStartDelegate OnHttpConnectStartCallback;

	UPROPERTY(BlueprintAssignable)
	FHttpConnectProcessDelegate OnHttpConnectProcessCallback;

	UPROPERTY(BlueprintAssignable)
	FHttpConnectFinishedDelegate OnHttpConnectFinishedCallback;

private:
	FHttpModule* HttpModule;

	void HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RevBytes);

	void HttpRequsetFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Respones, bool bWasSuccessful);

private:
	UPROPERTY()
	FString SourceURL;

	UPROPERTY()
	FString Path;

	UPROPERTY()
	FString Name;
};
