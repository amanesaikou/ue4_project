﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyBPLibrary.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

/**
 * 
 */

// 共通屬性
// 菁英弟子 裝備 祕笈等類別使用
USTRUCT(BlueprintType)
struct FCommonAttribute : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FCommonAttribute();

	int32 GetID() const;
	FString GetName() const;
	int32 GetAttack() const;
	int32 GetHealth() const;
	int32 GetDefense() const;

	void SetID(int32 tempID);
	void SetName(FString tempName);
	void SetAttack(int32 tempAttack);
	void SetHealth(int32 tempHealth);
	void SetDefense(int32 tempDefense);

	//
	UPROPERTY(BlueprintReadWrite)
	int32 id;
	
	// 名稱
	UPROPERTY(BlueprintReadWrite)
	FString name;

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

// 儲存功法的結構
USTRUCT(BlueprintType)
struct FLaw {
	GENERATED_BODY()
	FLaw() {};
	UPROPERTY(BlueprintReadWrite)
	FCommonAttribute attribute;
	UPROPERTY(BlueprintReadWrite)
	// 物品稀有度
	EItemRarityType rarity;
	UPROPERTY(BlueprintReadWrite)
	int32 price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECultivationType cultivationType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 lawLevel;
};

// 儲存裝備的結構
USTRUCT(BlueprintType)
struct FEquip {
	GENERATED_BODY()
	FEquip() {};

	UPROPERTY(BlueprintReadWrite)
	FCommonAttribute attribute;
	UPROPERTY(BlueprintReadWrite)
	EItemRarityType rarity;
	UPROPERTY(BlueprintReadWrite)
	int32 price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEquipmentType equipmentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 enhancementLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 refiningLevel;
};

// 物品基類
UCLASS()
class DEVELOP_API UItem : public UObject {

	GENERATED_BODY()

public:
	UItem();

	int32 GetID() const;

	UPROPERTY(BlueprintReadWrite)
	// 物品稀有度
	EItemRarityType rarity;

	UFUNCTION(BlueprintCallable)
	int32 GetPrice() const;

	UFUNCTION(BlueprintCallable)
	FString GetRarityName() const;

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

protected:
	// 物品屬性
	UPROPERTY(BlueprintReadWrite)
	FCommonAttribute attribute;
	
	UPROPERTY(BlueprintReadWrite)
	int32 price;

	void DecideRarity();

	UFUNCTION(BlueprintCallable)
	uint8 GetRarity() const;
};

UCLASS(BlueprintType)
class DEVELOP_API UEquipment : public UItem {

	GENERATED_BODY()

public:
	UEquipment();

	void Load(FEquip equipment);

	UFUNCTION(BlueprintCallable)
	FEquip Save();

	// 確定是哪種裝備
	void DecideType();

	UFUNCTION(BlueprintCallable)
	// 獲取裝備型態
	EEquipmentType GetType() const;

	// 根據裝備稀有度與種類讀表
	void DecideContent();

	UFUNCTION(BlueprintCallable)
	// 裝備強化
	void Enhance();

	UFUNCTION(BlueprintCallable)
	// 可以強化嗎
	bool CanEnhance(int32 spiritStone);

	UFUNCTION(BlueprintCallable)
	// 獲取強化費用
	int32 GetEnhancementCost() const;

	UFUNCTION(BlueprintCallable)
	// 裝備精煉
	void Refine();

	UFUNCTION(BlueprintCallable)
	// 可以精煉嗎
	bool CanRefine(int32 spiritStone);

	UFUNCTION(BlueprintCallable)
	// 獲取精煉費用
	int32 GetRefiningCost() const;

	UFUNCTION(BlueprintCallable)
	// 獲取強化等級
	int32 GetEnhancementLevel() const;

	UFUNCTION(BlueprintCallable)
	// 獲取精煉等級
	int32 GetRefiningLevel() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終攻擊
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終生命
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終防禦
	int32 GetFinallyDefense() const;
	
	// 強化等級與精煉等級的加成相乘
	float GetBuff() const;

private:
	EEquipmentType equipmentType;

	// 強化等級
	int32 enhancementLevel;

	// 精煉等級
	int32 refiningLevel;
};

// 修練法
UCLASS(BlueprintType)
class DEVELOP_API UCultivationLaw : public UItem {

	GENERATED_BODY()

public:
	UCultivationLaw();

	void Load(FLaw law);

	UFUNCTION(BlueprintCallable)
	FLaw Save();

	// 確定是哪種功法
	void DecideType();

	// 根據功法稀有度與種類讀表選擇功法
	void DecideLaw();

	UFUNCTION(BlueprintCallable)
	// 修練功法
	void LevelUp();

	UFUNCTION(BlueprintCallable)
	// 可以修練嗎?
	bool CanLevelUp(int32 spiritStone);

	UFUNCTION(BlueprintCallable)
	int32 GetLevel() const;

	void SetLevelZero();

	UFUNCTION(BlueprintCallable)
	// 獲取功法修練層次
	FString GetLevelName() const;

	UFUNCTION(BlueprintCallable)
	// 獲取功法修煉靈石花費
	int32 GetLevelUpCost() const;

	UFUNCTION(BlueprintCallable)
	ECultivationType GetType() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyDefense() const;

private:
	// 修練法種類
	ECultivationType cultivationType;

	// 修行等級
	int32 lawLevel;
};