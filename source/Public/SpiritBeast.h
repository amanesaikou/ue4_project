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

// 儲存靈獸的結構
USTRUCT(BlueprintType)
struct FSB {
	GENERATED_BODY()
	FSB() {};

	UPROPERTY(BlueprintReadWrite)
	FCommonAttribute attribute;
	UPROPERTY(BlueprintReadWrite)
	FPassiveSkill passiveSkill;
	UPROPERTY(BlueprintReadWrite)
	int32 star;
	UPROPERTY(BlueprintReadWrite)
	int32 blood;
	UPROPERTY(BlueprintReadWrite)
	int32 grade;
	UPROPERTY(BlueprintReadWrite)
	int32 price;
	UPROPERTY(BlueprintReadWrite)
	int32 bloodLineValue;
};

// 靈獸
UCLASS(BlueprintType)
class DEVELOP_API USpiritBeast : public UObject {
	GENERATED_BODY()

public:
	// 建構子
	USpiritBeast();

	void Load(FSB SB);

	UFUNCTION(BlueprintCallable)
	FSB Save();

	// 設定資料
	void DecideContent();

	// 決定天賦
	void DecidePassiveSkill();

	// 設定階級
	void DecideClass();

	// 決定星級
	void DecideStar();

	// 決定品級
	void DecideGrade();

	// 決定價錢
	void DecidePrice();

	UFUNCTION(BlueprintCallable)
	// 獲取名字
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	// 獲取星級
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
	// 獲取血脈等級
	int32 GetBlood() const;

	UFUNCTION(BlueprintCallable)
	// 獲取品級
	int32 GetGrade() const;

	UFUNCTION(BlueprintCallable)
	// 獲取天賦
	FPassiveSkill GetPassiveSkill() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終氣血
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終傷害
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終防禦
	int32 GetFinallyDefense() const;

	// 獲取增益效果
	float GetBuff() const;

	// 獲取天賦加成
	int32 WhichPassiveSkill(int32 index) const;

	UFUNCTION(BlueprintCallable)
	// 獲取出售價格
	int32 GetPrice() const;

	UFUNCTION(BlueprintCallable)
	// 使用血脈丹
	int32 UsePill(int32 value);

	UFUNCTION(BlueprintCallable)
	// 獲取血脈值
	int32 GetBloodLineValue() const;

	UFUNCTION(BlueprintCallable)
	// 獲取升級至下一等血脈的需求值
	int32 GetNextBloodValue() const;

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

	// 價格 
	int32 price;

	// 血脈值
	int32 bloodLineValue;
};
