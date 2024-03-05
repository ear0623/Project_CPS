// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPObject.h"



UHTTPObject::UHTTPObject()
{
	HttpModule = &FHttpModule::Get();
}

UHTTPObject::UHTTPObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HttpModule = &FHttpModule::Get();
}
void UHTTPObject::ExcuteHttp(FString Get_SourceURL, FString Path_1, FString Path_2, FString Get_Name)
{

	this->SourceURL = Get_SourceURL; // 3ㅣ=..ㄴㅇㄹ
	this->Path = "/api/vcmdata"; // api/vcmdata/getdata/5
	this->Path2 = Path_1;
	this->Path3 = Path_2;
	this->Name = Get_Name;
	FString URL;
	URL = SourceURL+Path+Path2+Path3+Path4;
	TSharedPtr<IHttpRequest> HttpRequest = HttpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(URL);
	HttpRequest->OnRequestProgress().BindUObject(this, &UHTTPObject::HttpRequestProgressDelegate);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHTTPObject::HttpRequsetFinishedDelegate);
	HttpRequest->ProcessRequest();
}

void UHTTPObject::MyHttpCall()
{

}

void UHTTPObject::HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RevBytes)
{
	int32 TotalSize = RequestPtr->GetResponse()->GetContentLength();
	float Percent = (float)RevBytes /TotalSize;
	OnHttpConnectProcessCallback.Broadcast(RevBytes, TotalSize, Percent);
}

void UHTTPObject::HttpRequsetFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Respones, bool bWasSuccessful)
{
	/*FString BasePath = FPaths::ConvertRelativePathToFull(FPaths::GameAgnosticSavedDir()) + Path;
	FString FileSavePath = BasePath + Name;
	if (Respones.IsValid() && EHttpResponseCodes::IsOk(Respones->GetResponseCode()))
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		PlatformFile.CreateDirectoryTree(*BasePath);
		IFileHandle* FileHandler = PlatformFile.OpenWrite(*FileSavePath);
		if (FileHandler)
		{
			FileHandler->Write(Respones->GetContent().GetData(), Respones->GetContentLength());
			FileHandler->Flush();

			delete FileHandler;
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
		}
	}
	else
	{
		bWasSuccessful = false;

	}
	OnHttpConnectFinishedCallback.Broadcast(bWasSuccessful, FileSavePath);*/
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject; // int, string, array, object, ...

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Respones->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject)) // 전체 오브젝트 파싱하기
	{
		TArray<TSharedPtr<FJsonValue> > DataArray = JsonObject->GetArrayField("data"); // 데이터 필드값 (어레이) 가져오기 -> 각 원소(오브젝트) 를 파싱할 예정
		for (auto data : DataArray)
		{
			FJsonSerializer::Deserialize(Reader, data); // 아이템 오브젝트 파싱하기
			SaveObject.SetItemId(data->AsObject()->GetIntegerField("itemId"));
			SaveObject.SetItemName(data->AsObject()->GetStringField("dataName"));
			SaveObject.SETDataValue(data->AsObject()->GetIntegerField("dataValue"));
			SaveObject.SETVcID(data->AsObject()->GetIntegerField("vcId"));
			SaveObject.SetVcName(data->AsObject()->GetStringField("vcName"));
			SaveObject.SETType(data->AsObject()->GetIntegerField("type"));
			// 각 필드값 가져오기
			// 가져온 값 조작
			HttpData.Broadcast(SaveObject.GetItemId(), SaveObject.GetItemName(), SaveObject.GetDataValue(), SaveObject.GetVcID(), SaveObject.GetVcName(), SaveObject.GetType()); 
		}
		bool login = JsonObject->GetBoolField("login");
		//이 클래스에서 선언하고 블루프린트에서 구현된 함수 호출
	
	
	}
}




