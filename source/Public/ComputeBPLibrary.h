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
};

class DEVELOP_API Message {
public:
	static FString GetEmployDisciple(FString rarity, FString name);

	static FString GetExpelDisciple(FString rarity, FString name);

	static FString GetNewEquipment(FString rarity, FString name, uint8 type);

	static FString GetNewEquipment(FString rarity, FString name, uint8 type, int32 price);

	static FString GetNewLaw(FString rarity, FString name, uint8 type);

	static FString GetNewLaw(FString rarity, FString name, uint8 type, int32 price);

	static FString GetSellItem(FString rarity, FString name, int32 price, uint8 type, int16 mode);

	static FString GetSellSpiritBeast(FString name, int32 price);

	static FString GetBuyItem(FString rarity, FString name, int32 price, uint8 type, int16 mode);

	static FString GetBuySpiritBeast(FString name, int32 price);

	static FString GetFacilityLevelUp(FString name, int32 lv, int32 cost);

	static TArray<FString> GetItemType(int32 mode);
};

UCLASS()
class DEVELOP_API UConstantBPLibrary : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:
	// 獲取弟子人數上限
	UFUNCTION(BlueprintCallable)
	static int32 GetDiscipleLimit();

	// 獲取物品數上限
	UFUNCTION(BlueprintCallable)
	static int32 GetItemLimit();

	// 獲取裝備強化等級上限
	UFUNCTION(BlueprintCallable)
	static int32 GetEnhanceLimit();

	// 獲取裝備精煉等級上限
	UFUNCTION(BlueprintCallable)
	static int32 GetRefineLimit();

	// 獲取功法修煉層次上限
	UFUNCTION(BlueprintCallable)
	static int32 GetLawLevelLimit();
};