// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Facility.generated.h"

/**
 * 
 */

 // 設施
USTRUCT(BlueprintType)
struct FFacility : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FFacility();

	void LevelUp();

	bool CanLevelUp();

	void SetValue(int32 newValue);

	FString GetName() const;

	int32 GetValue() const;

	int32 GetLevel() const;

	UPROPERTY(BlueprintReadWrite)
	FString name;

	UPROPERTY(BlueprintReadWrite)
	FString introduction;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	int32 level;
};
