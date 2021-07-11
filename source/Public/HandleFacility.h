// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleFacility.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleFacility : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 設施這年已經升級了嗎
	static bool HasLevelUp(FFacility facility);

	UFUNCTION(BlueprintCallable)
	// 
	static int32 GetLevelUpCost(FFacility facility);

	UFUNCTION(BlueprintCallable)
	// 設施可以升級嗎
	static bool CanLevelUp(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 設施升級
	static void LevelUp(USect* sect, int32 index);
	
	UFUNCTION(BlueprintCallable)
	// 可以煉製幾顆丹藥
	static int32 HowManyCanMake(USect* sect, FFacility facility);
};
