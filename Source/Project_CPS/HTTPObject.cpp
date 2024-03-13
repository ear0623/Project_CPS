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
	this->SourceURL = Get_SourceURL; // 3��=..������
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

	// �������� ���� json�� �𸮾󿡼� ��� ������ json���� ����
	FString ContentString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	if (!FJsonSerializer::Deserialize(Reader, JsonArray))
		return;

	// json �Ľ�
	FStructArray CallbackStruct; // �����͸� ������ ����

	FString result; // �����͸� ������ ����
	//int resultInt; // �����͸� ������ ����
	TArray<TSharedPtr<FJsonValue>> ResultArray;

	// CallbackStruct ����
	// Add ��� ��� ���� ��� ��� ��, �ش� ���� �־��־�� ���� ���� ����
	// �� ���� : CallbackStruct.FruitArray.Apple = result;
	// Add ��� ��� ��, �ش� ���� �־����� �� ��
	// �� ���� : CallbackStruct.FruitArray.Add();
	if (!JsonArray.IsEmpty()) // (JsonArray > 0)
		CallbackStruct.JsonData.SetNum(JsonArray.Num());

	// JsonArray ����
	for (int i = 0; i < JsonArray.Num(); i++)
	{
		// jsonArray to jsonValue
		TSharedPtr<FJsonValue>& JsonValue = JsonArray[i];

		// jsonValue to jsonObject
		if (JsonValue.IsValid() && JsonValue->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject>& JsonObject = JsonValue->AsObject();

			// jsonObject �˻�
			if (JsonObject.IsValid())
			{
				ParseParent(JsonObject, CallbackStruct);
			//	if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
			//	{
			//		CallbackStruct.JsonData[i].node_id = resultInt;
			//	}
			//	// TryGetStringField : Json�� String ���� �˻�
			//	if (JsonObject->TryGetStringField(TEXT("node_name"), result))
			//	{
			//		CallbackStruct.JsonData[i].node_name = result;
			//		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald,result);
			//	}

			//	// TryGetStringField : Json�� int/float�� ���� number ���� �˻�
			//	if (JsonObject->TryGetNumberField(TEXT("Total"), resultInt))
			//	{
			//		CallbackStruct.JsonData[i].Total = resultInt;
			//		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), resultInt));
			//	}
			//	//
			//	if (JsonObject->TryGetNumberField(TEXT("parent_id"), resultInt))
			//	{
			//		CallbackStruct.JsonData[i].parent_id = resultInt;
			//		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), resultInt));
			//	}
			//	if (JsonObject->TryGetStringField(TEXT("Type"), result))
			//	{
			//		CallbackStruct.JsonData[i].type = result;
			//		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, result);
			//	}
			//	TArray<TSharedPtr<FJsonValue>> TempChildArray = JsonObject->GetArrayField(TEXT("Child"));
			//	if (TempChildArray.Num() <= 0)
			//	{
			//		continue;
			//	}


			//	// �θ� ����Ľ��ϵ�, �ڽ� ��̵� �Ľ� -> ChildStruct �� ��̷� ��ȯ.
			//	TArray<FJsonFirstChildStruct> TempParsedChildArray;
			//	FJsonFirstChildStruct TempChild;
			//	//
			//	

			//	//
			//	for (int j = 0; j < TempChildArray.Num(); j++)
			//	{
			//		
			//		TSharedPtr<FJsonValue>& JsonChildValue = TempChildArray[j];
			//		// jsonValue to jsonObject
			//		if (JsonChildValue.IsValid() && JsonChildValue->Type == EJson::Object)
			//		{
			//			const TSharedPtr<FJsonObject>& JsonChildObject = JsonChildValue->AsObject();
			//			if (JsonChildValue.IsValid() && JsonChildValue->Type == EJson::Object)
			//			{
			//				// jsonObject �˻�
			//				if (JsonChildObject.IsValid())
			//				{
			//					if (JsonChildObject->TryGetNumberField(TEXT("node_id"), resultInt))
			//					{
			//						TempChild.node_id = resultInt;
			//					}
			//					// TryGetStringField : Json�� String ���� �˻�
			//					if (JsonChildObject->TryGetStringField(TEXT("node_name"), result))
			//					{
			//						TempChild.node_name = result;
			//						GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, result);
			//					}
			//					//
			//					if (JsonChildObject->TryGetNumberField(TEXT("parent_id"), resultInt))
			//					{
			//						TempChild.parent_id = resultInt;
			//					}
			//					if (JsonChildObject->TryGetStringField(TEXT("Type"), result))
			//					{
			//						TempChild.type = result;
			//					}

			//					TArray<TSharedPtr<FJsonValue>> TempChildSecondArray = JsonObject->GetArrayField(TEXT("Child"));
			//					if (TempChildSecondArray.Num() <= 0)
			//					{
			//						continue;
			//					}

			//					TempParsedChildArray.Add(TempChild); 
			//					// grand children
		

			//					for (int k = 0; k < TempChildSecondArray.Num(); k++)
			//					{
			//						TSharedPtr<FJsonValue>& JsonGrandChildValue = TempChildSecondArray[j];
			//						if (JsonGrandChildValue.IsValid() && JsonGrandChildValue->Type == EJson::Object)
			//						{
			//							const TSharedPtr<FJsonObject>& JsonGrandChildObject = JsonGrandChildValue->AsObject();
			//							if (JsonGrandChildValue.IsValid() && JsonGrandChildValue->Type == EJson::Object)
			//							{
			//								if (JsonGrandChildObject.IsValid())
			//								{
			//									if (JsonGrandChildObject->TryGetNumberField(TEXT("node_id"), resultInt))
			//									{
			//											TempGrandChild.node_id = resultInt;
			//									}
			//									// TryGetStringField : Json�� String ���� �˻�													
			//									if (JsonGrandChildObject->TryGetStringField(TEXT("node_name"), result))
			//									{
			//										TempGrandChild.node_name = result;
			//										GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Black, result);
			//									}
			//									if (JsonGrandChildObject->TryGetNumberField(TEXT("parent_id"), resultInt))
			//										{
			//											TempGrandChild.parent_id = resultInt;
			//										}
			//									if (JsonGrandChildObject->TryGetStringField(TEXT("Type"), result))
			//										{
			//											TempGrandChild.type = result;
			//										}
			//									TempSaveSecondChildArray.Add(TempGrandChild);

			//									TArray<TSharedPtr<FJsonValue>> TempChildThirdArray = JsonObject->GetArrayField(TEXT("Child"));
			//									if (TempChildSecondArray.Num() <= 0)
			//									{
			//										continue;
			//									}
			//									for (int l = 0; l < TempChildThirdArray.Num(); l++)
			//									{
			//										TSharedPtr<FJsonValue>& JsonGrandGrandChildValue = TempChildThirdArray[j];
			//										if (JsonGrandGrandChildValue.IsValid() && JsonGrandGrandChildValue->Type == EJson::Object)
			//										{
			//											const TSharedPtr<FJsonObject>& JsonGrandGrandChildObject = JsonGrandGrandChildValue->AsObject();
			//											if (JsonGrandGrandChildValue.IsValid() && JsonGrandGrandChildValue->Type == EJson::Object)
			//											{
			//												if (JsonGrandGrandChildObject.IsValid())
			//												{
			//													if (JsonGrandGrandChildObject->TryGetNumberField(TEXT("node_id"), resultInt))
			//													{
			//														TempGrandGrandChild.node_id = resultInt;
			//													}
			//													// TryGetStringField : Json�� String ���� �˻�													
			//													if (JsonGrandGrandChildObject->TryGetStringField(TEXT("node_name"), result))
			//													{
			//														TempGrandGrandChild.node_name = result;
			//														GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Cyan, result);
			//													}
			//													if (JsonGrandGrandChildObject->TryGetNumberField(TEXT("parent_id"), resultInt))
			//													{
			//														TempGrandGrandChild.parent_id = resultInt;
			//													}
			//													if (JsonGrandGrandChildObject->TryGetStringField(TEXT("Type"), result))
			//													{
			//														TempGrandGrandChild.type = result;
			//													}
			//													TempSaveThirdChildArray.Add(TempGrandGrandChild);
			//												}
			//											}
			//										}
			//									}
			//							

			//								}
			//							}
			//						}
			//						TempSaveSecondChildArray[k].JsonThirdChildData = TempSaveThirdChildArray;
			//					}
			//							
			//				}
			//			}
			//		}
			//		TempParsedChildArray[j].JsonSecondChildData = TempSaveSecondChildArray;
			//	}
			//	//CallbackStruct.JsonData[i].JsonFirstChildData = TempParsedChildArray;
			//	CallbackStruct.JsonData[i].JsonFirstChildData = TempParsedChildArray;
			}
		}
		Count += 1;
		SaveObject.SetLoopcount(Count);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), Count));
		// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
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
	//if (FJsonSerializer::Deserialize(Reader, JsonObject)) // ��ü ������Ʈ �Ľ��ϱ�
	//{
	//	TArray<TSharedPtr<FJsonValue> > DataArray = JsonObject->GetArrayField("data"); // ������ �ʵ尪 (���) �������� -> �� ����(������Ʈ) �� �Ľ��� ����
	//	for (auto data : DataArray)
	//	{
	//		FJsonSerializer::Deserialize(Reader, data); // ������ ������Ʈ �Ľ��ϱ�
	//		SaveObject.SetItemId(data->AsObject()->GetIntegerField("node_id"));
	//		SaveObject.SetItemName(data->AsObject()->GetStringField("dataName"));
	//		SaveObject.SETDataValue(data->AsObject()->GetIntegerField("dataValue"));
	//		SaveObject.SETVcID(data->AsObject()->GetIntegerField("vcId"));
	//		SaveObject.SetVcName(data->AsObject()->GetStringField("vcName"));
	//		SaveObject.SETType(data->AsObject()->GetIntegerField("type"));
	//		Count += 1;
	//		SaveObject.SetLoopcount(Count);
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Emerald, FString::Printf(TEXT("%d"), Count));
	//		// �� �ʵ尪 ��������
	//		// ������ �� ����
	//		HttpData.Broadcast(SaveObject.GetItemId(), SaveObject.GetItemName(), SaveObject.GetDataValue(), SaveObject.GetVcID(), SaveObject.GetVcName(), SaveObject.GetType());
	//		if (MyHud)
	//		{
	//			MyHud->ConnectTest(SaveObject.GetItemId(), SaveObject.GetItemName(), SaveObject.GetDataValue(), SaveObject.GetVcID(), SaveObject.GetVcName(), SaveObject.GetType());
	//		}

	//	}
		bool login = JsonObject->GetBoolField("login");
		//�� Ŭ�������� �����ϰ� �������Ʈ���� ������ �Լ� ȣ��
	//}
}


void UHTTPObject::ParseParent(const TSharedPtr<FJsonObject>& JsonObject, FStructArray& CallbackStruct)
{
	FString result;
	int resultInt;

	FJsonStruct Parents;


	if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
		Parents.node_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("node_name"), result))
		Parents.node_name = result;

	if (JsonObject->TryGetNumberField(TEXT("parent_id"), resultInt))
		Parents.parent_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("Type"), result))
		Parents.type = result;

	TArray<TSharedPtr<FJsonValue>> ChildArray = JsonObject->GetArrayField(TEXT("Child"));
	for (int i = 0; i < ChildArray.Num(); i++)
	{
		TSharedPtr<FJsonValue>& ChildValue = ChildArray[i];
		if (ChildValue.IsValid() && ChildValue->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject>& ChildObject = ChildValue->AsObject();
			if (ChildObject.IsValid())
			{
				ParseZeroChild(ChildObject, Parents);
			}
		}
	}

	CallbackStruct.JsonData.Add(Parents);
}

void UHTTPObject::ParseZeroChild(const TSharedPtr<FJsonObject>& JsonObject, FJsonStruct& ZeroChild)
{
	FString result;
	int resultInt;

	FJsonFirstChildStruct FirstChild;

	if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
		FirstChild.node_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("node_name"), result))
		FirstChild.node_name = result;

	if (JsonObject->TryGetNumberField(TEXT("parent_id"), resultInt))
		FirstChild.parent_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("Type"), result))
		FirstChild.type = result;

	TArray<TSharedPtr<FJsonValue>> ChildArray = JsonObject->GetArrayField(TEXT("Child"));
	for (int i = 0; i < ChildArray.Num(); i++)
	{
		TSharedPtr<FJsonValue>& ChildValue = ChildArray[i];
		if (ChildValue.IsValid() && ChildValue->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject>& ChildObject = ChildValue->AsObject();
			if (ChildObject.IsValid())
			{
				ParseFirstChild(ChildObject, FirstChild);
			}
		}
	}

	ZeroChild.JsonFirstChildData.Add(FirstChild);
}

void UHTTPObject::ParseFirstChild(const TSharedPtr<FJsonObject>& JsonObject, FJsonFirstChildStruct& FirstChild)
{
	FString result;
	int resultInt;

	FJsonSecondChildStruct SeoncdChild;

	if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
		SeoncdChild.node_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("node_name"), result))
		SeoncdChild.node_name = result;

	if (JsonObject->TryGetNumberField(TEXT("parent_id"), resultInt))
		SeoncdChild.parent_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("Type"), result))
		SeoncdChild.type = result;

	TArray<TSharedPtr<FJsonValue>> ChildArray = JsonObject->GetArrayField(TEXT("Child"));
	for (int i = 0; i < ChildArray.Num(); i++)
	{
		TSharedPtr<FJsonValue>& ChildValue = ChildArray[i];
		if (ChildValue.IsValid() && ChildValue->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject>& ChildObject = ChildValue->AsObject();
			if (ChildObject.IsValid())
			{
				ParseSecondChild(ChildObject, SeoncdChild);
			}
		}
	}

	FirstChild.JsonSecondChildData.Add(SeoncdChild);
}


void UHTTPObject::ParseSecondChild(const TSharedPtr<FJsonObject>& JsonObject, FJsonSecondChildStruct& SecondChild)
{
	FString result;
	int resultInt;

	FJsonThirdChildStruct ThridChild;

	if (JsonObject->TryGetNumberField(TEXT("node_id"), resultInt))
		ThridChild.node_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("node_name"), result))
		ThridChild.node_name = result;

	if (JsonObject->TryGetNumberField(TEXT("parent_id"), resultInt))
		ThridChild.parent_id = resultInt;

	if (JsonObject->TryGetStringField(TEXT("Type"), result))
		ThridChild.type = result;

	SecondChild.JsonThirdChildData.Add(ThridChild);
}

