// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDatabase.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

AMyDatabase::AMyDatabase() {
    HTTP = &FHttpModule::Get();
}

void AMyDatabase::MyHTTPMethod(FString itemName, uint8 itemRarity) {
    /*
    // Jsonデータの作成
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("Item_Name", itemName);
    JsonObject->SetNumberField("Item_Rarity", itemRarity);

    // OutputStringにJson書き出し
    FString OutputString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

    // Httpリクエストの作成
    TSharedRef<IHttpRequest> Request = HTTP->CreateRequest();
    Request->SetURL("http://localhost:80/test.php");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));
    Request->SetContentAsString(OutputString);
    Request->OnProcessRequestComplete().BindUObject(this, &AMyDatabase::OnResponseReceived);
    Request->ProcessRequest();
    */
}

void AMyDatabase::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
    return;
}
