// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HTTPObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpConnectStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpConnectProcessDelegate, int32, RecvSize, int32, TotalSize, float, Percent); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHttpConnectFinishedDelegate, bool, bIsSuccess, FString, ContentPath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FDeleGetHTTPData, int64, Id, FString, DataName, int64, DataValue, int64, VCID, FString, VCName, int64, Type);


USTRUCT(BlueprintType)
struct FSaveIndexStruct : public FTableRowBase 
{
	GENERATED_BODY()


	FSaveIndexStruct() :ItemId(1), ItemName(" "), DataValue(1), VcID(1), VcName(" "), Type(1) {}
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 DataValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 VcID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString VcName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 Type;
public:
	int64 GetItemId() { return ItemId; }
	void SetItemId(int64 itemId) { ItemId = itemId; }
	//
	FString GetItemName() { return ItemName; }
	void SetItemName(FString itemName) { ItemName = itemName; }
	//
	int64 GetDataValue() { return DataValue; }
	void SETDataValue(int64 dataValue) { DataValue = dataValue; }
	//
	int64 GetVcID() { return VcID; }
	void SETVcID(int64 vcID) { VcID = vcID; }
	//
	FString GetVcName() { return VcName; }
	void SetVcName(FString vcName) { VcName = vcName; }
	//
	int64 GetType() { return Type; }
	void SETType(int64 type) { Type = type; }
};

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_CPS_API UHTTPObject : public UObject
{
	GENERATED_BODY()
	
	UHTTPObject(const class FObjectInitializer& ObjectInitializer);

public:
	UHTTPObject();

	UFUNCTION(BlueprintCallable,Category = "HTTP", DisplayName = "HttpConnect")
	void ExcuteHttp(FString SourceURL, FString Path_1, FString Path_2, FString Name);

	UPROPERTY(BlueprintAssignable)
	FHttpConnectStartDelegate OnHttpConnectStartCallback;

	UPROPERTY(BlueprintAssignable)
	FHttpConnectProcessDelegate OnHttpConnectProcessCallback;

	UPROPERTY(BlueprintAssignable)
	FHttpConnectFinishedDelegate OnHttpConnectFinishedCallback;

	UFUNCTION()
	void MyHttpCall();



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
	FString Path2;

	UPROPERTY()
	FString Path3;

	UPROPERTY()
	FString Path4;

	UPROPERTY()
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " Struct", meta = (AllowPrivateAccess = "true"))
	FDeleGetHTTPData HttpData;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category =" Struct", meta = (AllowPrivateAccess = "true"))
	FSaveIndexStruct SaveObject;

public:

	FDeleGetHTTPData GetHttpData() { return HttpData;}


	FSaveIndexStruct GetSaveObject() { return SaveObject; }

public:

	//
};
