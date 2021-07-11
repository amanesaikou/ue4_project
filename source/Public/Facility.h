// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Facility.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FFacility : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FFacility();

	// 獲取升級花費
	int32 GetLevelUpCost();

	bool IsLevelMax();

	void LevelUp();

	void Update();

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText introduction;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	int32 level;

	bool hasLevelUp = false;
};