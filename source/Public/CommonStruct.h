// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CommonStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FReadText : public FTableRowBase {
	GENERATED_BODY()
	
	FReadText() {};

	UPROPERTY(BlueprintReadWrite)
	FText str;
};

USTRUCT(BlueprintType)
struct FReadStr : public FTableRowBase {
	GENERATED_BODY()

	FReadStr() {};

	UPROPERTY(BlueprintReadWrite)
	FString str;
};

USTRUCT(BlueprintType)
struct FCommonAttribute : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FCommonAttribute();

	//
	UPROPERTY(BlueprintReadWrite)
	int32 id;

	// 名稱
	UPROPERTY(BlueprintReadWrite)
	FText name;

	// 攻擊力
	UPROPERTY(BlueprintReadWrite)
	int32 attack;

	// 血量
	UPROPERTY(BlueprintReadWrite)
	int32 health;

	// 防禦
	UPROPERTY(BlueprintReadWrite)
	int32 defense;
};
