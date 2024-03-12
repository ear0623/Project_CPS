// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPObject.h"
#include "CPSHUD.h"
#include "Kismet/GameplayStatics.h"
#include "USideSecondWidget.h"




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
	MyHttpCall();
	this->SourceURL = Get_SourceURL; // 3ㅣ=..ㄴㅇㄹ
	this->Path = "/api/vcmdata"; // api/vcmdata/getdata/5
	this->Path2 = Path_1;
	this->Path3 = Path_2;
	this->Name = Get_Name;
	FString URL;
	URL = SourceURL+Path2+Path3+Path4;
	TSharedPtr<IHttpRequest> HttpRequest = HttpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(URL);
	HttpRequest->OnRequestProgress().BindUObject(this, &UHTTPObject::HttpRequestProgressDelegate);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHTTPObject::HttpRequsetFinishedDelegate);
	HttpRequest->ProcessRequest();
}

void UHTTPObject::MyHttpCall()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AHUD* Hud = PlayerController->GetHUD();
		if (Hud)
		{
			MyHud = dynamic_cast<ACPSHUD*>(Hud);
		}
	}
}

void UHTTPObject::HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RevBytes)
{
	int32 TotalSize = RequestPtr->GetResponse()->GetContentLength();
	float Percent = (float)RevBytes /TotalSize;
	OnHttpConnectProcessCallback.Broadcast(RevBytes, TotalSize, Percent);
}

void UHTTPObject::HttpRequsetFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	FSaveIndexStruct ResponseDataStruct;

	if (!bWasSuccessful)
		return;

	// 서버에서 받은 json을 언리얼에서 사용 가능한 json으로 변경
	FString ContentString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	if (!FJsonSerializer::Deserialize(Reader, JsonArray))
		return;

	// json 파싱
	FStructArray CallbackStruct; // 데이터를 저장할 변수
	FString result; // 데이터를 저장할 변수
	int resultInt; // 데이터를 저장할 변수
	TArray<TSharedPtr<FJsonValue>> ResultArray;

	// CallbackStruct 세팅
	// Add 방식 대신 대입 방식 사용 시, 해당 과정 넣어주어야 에러 나지 않음
	// ㄴ 예시 : CallbackStruct.FruitArray.Apple = result;
	// Add 방식 사용 시, 해당 과정 넣어주지 말 것
	// ㄴ 예시 : CallbackStruct.FruitArray.Add();
	if (!JsonArray.IsEmpty()) // (JsonArray > 0)
		CallbackStruct.JsonData.SetNum(JsonArray.Num());

	// JsonArray 접근
	for (int i = 0; i < JsonArray.Num(); i++)
	{
		// jsonArray to jsonValue
		TSharedPtr<FJsonValue>& JsonValue = JsonArray[i];

		// jsonValue to jsonObject
		if (JsonValue.IsValid() && JsonValue->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject>& JsonObject = JsonValue->AsObject();

			// jsonObject 검사
			if (JsonObject.IsValid())
			{
				if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
				{
					CallbackStruct.JsonData[i].node_id = resultInt;
				}
				// TryGetStringField : Json의 String 변수 검사
				if (JsonObject->TryGetStringField(TEXT("node_name"), result))
				{
					CallbackStruct.JsonData[i].node_name = result;
					GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald,result);
				}

				// TryGetStringField : Json의 int/float와 같은 number 변수 검사
				if (JsonObject->TryGetNumberField(TEXT("Total"), resultInt))
				{
					CallbackStruct.JsonData[i].Total = resultInt;
					//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), resultInt));
				}
				//
				if (JsonObject->TryGetNumberField(TEXT("parent_id"), resultInt))
				{
					CallbackStruct.JsonData[i].parent_id = resultInt;
					//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), resultInt));
				}
				if (JsonObject->TryGetStringField(TEXT("Type"), result))
				{
					CallbackStruct.JsonData[i].type = result;
					//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, result);
				}
				TArray<TSharedPtr<FJsonValue>> TempChildArray = JsonObject->GetArrayField(TEXT("Child"));
				if (TempChildArray.Num() <= 0)
				{
					continue;
				}


				// 부모 어레이파싱하듯, 자식 어레이도 파싱 -> ChildStruct 의 어레이로 반환.
				TArray<FJsonFirstChildStruct> TempParsedChildArray;
				FJsonFirstChildStruct TempChild;
				//
				

				//
				for (int j = 0; j < TempChildArray.Num(); j++)
				{
					
					TSharedPtr<FJsonValue>& JsonChildValue = TempChildArray[j];
					// jsonValue to jsonObject
					if (JsonChildValue.IsValid() && JsonChildValue->Type == EJson::Object)
					{
						const TSharedPtr<FJsonObject>& JsonChildObject = JsonChildValue->AsObject();
						if (JsonChildValue.IsValid() && JsonChildValue->Type == EJson::Object)
						{
							// jsonObject 검사
							if (JsonChildObject.IsValid())
							{
								if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
								{
									TempChild.node_id = resultInt;
								}
								// TryGetStringField : Json의 String 변수 검사
								if (JsonChildObject->TryGetStringField(TEXT("node_name"), result))
								{
									TempChild.node_name = result;
									GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, result);
								}
								//
								if (JsonChildObject->TryGetNumberField(TEXT("parent_id"), resultInt))
								{
									TempChild.parent_id = resultInt;
								}
								if (JsonChildObject->TryGetStringField(TEXT("Type"), result))
								{
									TempChild.type = result;
								}

								TArray<TSharedPtr<FJsonValue>> TempChildSecondArray = JsonObject->GetArrayField(TEXT("Child"));
								if (TempChildSecondArray.Num() <= 0)
								{
									continue;
								}
								
								TempParsedChildArray.Add(TempChild);

								TArray<FJsonSecondChildStruct> TempSecondChildArray;
								FJsonSecondChildStruct TempSecondChild;
						
								for (int k = 0; k < TempChildSecondArray.Num(); k++)
								{
									TSharedPtr<FJsonValue>& JsonSecondChildValue = TempChildSecondArray[j];
									// jsonValue to jsonObject
									if (JsonSecondChildValue.IsValid() && JsonSecondChildValue->Type == EJson::Object)
									{
										const TSharedPtr<FJsonObject>& JsonSecondChildObject = JsonSecondChildValue->AsObject();
										if (JsonSecondChildObject.IsValid() && JsonSecondChildValue->Type == EJson::Object)
										{
											// jsonObject 검사
											if (JsonSecondChildObject.IsValid())
											{
												if (JsonSecondChildObject->TryGetNumberField(TEXT("node_id"), resultInt))
												{
													TempSecondChild.node_id = resultInt;
												}
												// TryGetStringField : Json의 String 변수 검사
								//				if (JsonSecondChildObject->TryGetStringField(TEXT("node_name"), result))
								//				{
								//					TempSecondChild.node_name = result;
								//					GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Blue, result);
								//				}
								//				//
								//				if (JsonSecondChildObject->TryGetNumberField(TEXT("parent_id"), resultInt))
								//				{
								//					TempSecondChild.parent_id = resultInt;
								//				}
								//				if (JsonSecondChildObject->TryGetStringField(TEXT("Type"), result))
								//				{
								//					TempSecondChild.type = result;
								//				}
								//				TArray<FJsonThirdChildStruct> JsonThirdChildArray;
												TempSecondChildArray.Add(TempSecondChild);
											}
										}
									}
									
								}
								CallbackStruct.JsonData[i].JsonFirstChildData[j].JsonSecondChildData = TempSecondChildArray;
								
							}
							
						}
					}
				}
				CallbackStruct.JsonData[i].JsonFirstChildData = TempParsedChildArray;
			}
		}
		Count += 1;
		SaveObject.SetLoopcount(Count);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), Count));
		// 파싱 데이터 사용 (해당 함수에서는 델리게이트 사용, 다른 방식으로 사용 가능)
		JSonCallBack.Broadcast(CallbackStruct);
		
	}
}

void UHTTPObject::Tempsave()
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
	TSharedPtr<FJsonObject>  JsonObject;

	//Create a pointer to hold the json serialized data
	// int, string, array, object, ...

	//Create a reader pointer to read the json data
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	//if (FJsonSerializer::Deserialize(Reader, JsonObject)) // 전체 오브젝트 파싱하기
	//{
	//	TArray<TSharedPtr<FJsonValue> > DataArray = JsonObject->GetArrayField("data"); // 데이터 필드값 (어레이) 가져오기 -> 각 원소(오브젝트) 를 파싱할 예정
	//	for (auto data : DataArray)
	//	{
	//		FJsonSerializer::Deserialize(Reader, data); // 아이템 오브젝트 파싱하기
	//		SaveObject.SetItemId(data->AsObject()->GetIntegerField("node_id"));
	//		SaveObject.SetItemName(data->AsObject()->GetStringField("dataName"));
	//		SaveObject.SETDataValue(data->AsObject()->GetIntegerField("dataValue"));
	//		SaveObject.SETVcID(data->AsObject()->GetIntegerField("vcId"));
	//		SaveObject.SetVcName(data->AsObject()->GetStringField("vcName"));
	//		SaveObject.SETType(data->AsObject()->GetIntegerField("type"));
	//		Count += 1;
	//		SaveObject.SetLoopcount(Count);
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), Count));
	//		// 각 필드값 가져오기
	//		// 가져온 값 조작
	//		HttpData.Broadcast(SaveObject.GetItemId(), SaveObject.GetItemName(), SaveObject.GetDataValue(), SaveObject.GetVcID(), SaveObject.GetVcName(), SaveObject.GetType());
	//		if (MyHud)
	//		{
	//			MyHud->ConnectTest(SaveObject.GetItemId(), SaveObject.GetItemName(), SaveObject.GetDataValue(), SaveObject.GetVcID(), SaveObject.GetVcName(), SaveObject.GetType());
	//		}

	//	}
		bool login = JsonObject->GetBoolField("login");
		//이 클래스에서 선언하고 블루프린트에서 구현된 함수 호출
	//}
}




