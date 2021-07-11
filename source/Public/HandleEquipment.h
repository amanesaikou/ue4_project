// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleEquipment.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleEquipment : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static void AddEquipment(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void AddSingleEquipment(USect* sect, FEquipment equipment);

	UFUNCTION(BlueprintCallable)
	static bool CanAddEquipment(USect* sect, EEquipmentType type);
	
	UFUNCTION(BlueprintCallable)
	static void Sort(USect* sect, int32 mode);

	UFUNCTION(BlueprintCallable)
	static bool HasEquipment(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static void SellEquipment(USect* sect, int32 index, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	static FText GetName(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetHealth(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetDamage(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetDefense(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static bool CanEnhance(USect* sect, FEquipment e);

	UFUNCTION(BlueprintCallable)
	static bool Enhance(USect* sect, int32 index, int32 which, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	static int32 GetSingleEquipmentNum(USect* sect, EEquipmentType type);
};
