// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "MyDatabase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTURNGAME_API AMyDatabase : public AActor
{
	GENERATED_BODY()

public:

	AMyDatabase();

	UFUNCTION(BlueprintCallable, Category = "Http")
	void MyHTTPMethod(FString itemName, uint8 itemRarity);

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FHttpModule* HTTP;
	
};
