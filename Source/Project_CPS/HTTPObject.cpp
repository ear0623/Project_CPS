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
	//
	if (Path_1 + Path2 == Path)
	{
		//������ ���� if������ �߰� ����;
		APIENum = SettingAPI::Type01;
	}
	else
	{
		APIENum = SettingAPI::None; 
	}
	//
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
				switch (APIENum)
				{
				case SettingAPI::None:
					ParseParent(JsonObject, CallbackStruct);
					break;
				case SettingAPI::Type01:
					ParseParent_Type01(JsonObject, CallbackStruct);
					break;
				case SettingAPI::Type02:
					break;
				default:
					break;
				}
				
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

	
	TSharedPtr<FJsonObject>  JsonObject;



	bool login = JsonObject->GetBoolField("login");
	
	
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

void UHTTPObject::ParseParent_Type01(const TSharedPtr<FJsonObject>& JsonObject, FStructArray& CallbackStruct)
{
	FString result;
	int resultInt;

	FJsonType01Struct Parents;


	if (JsonObject->TryGetNumberField(TEXT("itemId"), resultInt))
		Parents.itemId = resultInt;

	if (JsonObject->TryGetStringField(TEXT("dataName"), result))
		Parents.dataName = result;

	if (JsonObject->TryGetNumberField(TEXT("dataValue"), resultInt))
		Parents.dataValue = resultInt;

	if (JsonObject->TryGetStringField(TEXT("vcName"), result))
		Parents.vcName = result;

	if (JsonObject->TryGetNumberField(TEXT("vcId"), resultInt))
		Parents.vcId = resultInt;

	if (JsonObject->TryGetNumberField(TEXT("type"), resultInt))
		Parents.type = resultInt;


	CallbackStruct.JsonData_Type01.Add(Parents);
}

