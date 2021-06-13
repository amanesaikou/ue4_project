// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ComputeBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOP_API UComputeBPLibrary : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static float GetRemainingPercent(int32 original, int32 after);

	UFUNCTION(BlueprintCallable)
	static int32 GetRemainingHealth(int32 targetAttack, int32 sourceHealth, int32 sourceDefense);

	static int32 CheckOverRange(int32 value, int32 limit);

	UFUNCTION(BlueprintCallable)
	static int32 From64To32(int64 value);
};


class DEVELOP_API Message {
public:
	static FString GetEmployDisciple(FString rarity, FString name);

	static FString GetNewEquipment(FString rarity, FString name, uint8 type);

	static FString GetNewEquipment(FString rarity, FString name, uint8 type, int32 price);

	static FString GetNewLaw(FString rarity, FString name, uint8 type);

	static FString GetNewLaw(FString rarity, FString name, uint8 type, int32 price);

	static FString GetFacilityLevelUp(FString name, int32 lv, int32 cost);
};