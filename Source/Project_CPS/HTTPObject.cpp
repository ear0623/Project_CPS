// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPObject.h"

UHTTPObject::UHTTPObject()
{
	HttpModule = &FHttpModule::Get();
}

void UHTTPObject::ExcuteHttp(FString Get_SourceURL, FString Get_Path, FString Get_Name)
{
	this->SourceURL = Get_SourceURL;
	this->Path = Get_Path;
	this->Name = Get_Name;

	TSharedPtr<IHttpRequest> HttpRequest = HttpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(this->SourceURL);
	HttpRequest->OnRequestProgress().BindUObject(this, &UHTTPObject::HttpRequestProgressDelegate);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHTTPObject::HttpRequsetFinishedDelegate);

	HttpRequest->ProcessRequest();
	
}

void UHTTPObject::HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RevBytes)
{
	int32 TotalSize = RequestPtr->GetResponse()->GetContentLength();
	float Percent = (float)RevBytes /TotalSize;
	OnHttpConnectProcessCallback.Broadcast(RevBytes, TotalSize, Percent);
}

void UHTTPObject::HttpRequsetFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Respones, bool bWasSuccessful)
{
	FString BasePath = FPaths::ConvertRelativePathToFull(FPaths::GameAgnosticSavedDir()) + Path;
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
	OnHttpConnectFinishedCallback.Broadcast(bWasSuccessful, FileSavePath);
}
