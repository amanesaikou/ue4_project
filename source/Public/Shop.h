// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Law.h"
#include "Elixirs.h"
#include "SpiritBeast.h"
#include "Shop.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FShop {

	GENERATED_BODY()

	FShop();

	void UpdateGood(TArray<FLaw> noGet);

	void UpdateEquipments();

	void UpdateLaws(TArray<FLaw>& noGet);

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> equips;

	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> laws;

	UPROPERTY(BlueprintReadWrite)
	TArray<FSpiritBeast> spiritBeasts;

};
