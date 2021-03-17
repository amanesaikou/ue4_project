// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTURNGAME_API UMyBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static void ImportDLL();

	//UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static int ComputeProperty(int value, uint8& rarity, int& max);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static float ComputeDamage(float sourceAttack, float sourceCS, float targetDefense, int baseDamage);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static void FreeDLL();
	
};

// 整数の乱数を取得する
int GetRandomInt(int min, int max);
