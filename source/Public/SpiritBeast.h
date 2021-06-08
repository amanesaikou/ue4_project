// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyBPLibrary.h"
#include "Item.h"
#include "SpiritBeast.generated.h"

/**
 * 
 */


 // 
USTRUCT(BlueprintType)
struct FPassiveSkill : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FPassiveSkill();

	EPassiveSkill GetPassiveSkill() const;

	FString GetName() const;

	int32 GetValue() const;

	UPROPERTY(BlueprintReadWrite)
	EPassiveSkill type;

	UPROPERTY(BlueprintReadWrite)
	FString name;

	UPROPERTY(BlueprintReadWrite)
	int32 value;
};

// 靈獸
UCLASS(BlueprintType)
class DEVELOP_API USpiritBeast : public UObject {
	GENERATED_BODY()

public:
	USpiritBeast();

	void DecideContent();

	void DecidePassiveSkill();

	// 設定階級
	void DecideClass();

	// 決定星級
	void DecideStar();

	// 決定品級
	void DecideGrade();

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBlood() const;

	UFUNCTION(BlueprintCallable)
	int32 GetGrade() const;

	UFUNCTION(BlueprintCallable)
	FPassiveSkill GetPassiveSkill() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyDefense() const;

	float GetBuff() const;

	// 獲取天賦加成
	int32 WhichPassiveSkill(int32 index) const;

private:
	// 屬性
	FCommonAttribute attribute;

	// 天賦
	FPassiveSkill passiveSkill;

	// 星級
	int32 star;

	// 血脈濃度
	int32 blood;

	// 品級
	int32 grade;
};
