// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleShop.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleShop : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 獲取裝備價格
	static int32 GetEquipmentPrice(FEquipment equipment);

	UFUNCTION(BlueprintCallable)
	// 靈石夠買裝備嗎
	static bool CanBuyEquipment(USect* sect, FEquipment equipment);

	UFUNCTION(BlueprintCallable)
	// 裝備欄有位置放嗎
	static bool CanAddEquipment(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 買裝備
	static void BuyEquipment(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static bool CanBuyLaw(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static void BuyLaw(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static bool CanBuySpiritBeast(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static bool CanAddSpiritBeast(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void AddSpiritBeast(USect* sect, int32 index);
};
