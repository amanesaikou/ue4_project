// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AllEnum.h"
#include "SpiritBeast.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FPassiveSkill : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FPassiveSkill();

	UPROPERTY(BlueprintReadWrite)
	EPassiveSkill type;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText effect;

	UPROPERTY(BlueprintReadWrite)
	int32 value;
};

USTRUCT(BlueprintType)
struct FSpiritBeast : public FTableRowBase {

	GENERATED_BODY()

	FSpiritBeast();

	void SetPassive();

	void Setting();

	void Growth();

	bool IsDeath();

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText content;

	UPROPERTY(BlueprintReadWrite)
	int32 health;

	UPROPERTY(BlueprintReadWrite)
	int32 attack;

	UPROPERTY(BlueprintReadWrite)
	int32 defense;

	FPassiveSkill passive;

	EGrowing growing;

	EBlood blood;

	int32 age = 0;

	int32 price = 0;
};
