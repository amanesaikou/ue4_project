// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnum.h"
#include "Equipment.h"
#include "Law.h"
#include "Elixirs.h"
#include "Disciple.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWife {
	GENERATED_BODY()

	FWife();

	void Create();

	void DecideName();

	void DecideAppearance();

	void DecidePersonality();

	void SetBuff(float cbuff, int32 cspeed, int32 CP, float CS);

	UPROPERTY(BlueprintReadWrite)
	FText surname;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	EAppearance appearance;

	UPROPERTY(BlueprintReadWrite)
	EWPersonality personality;

	UPROPERTY(BlueprintReadWrite)
	float buff;

	UPROPERTY(BlueprintReadWrite)
	int32 speed;

	UPROPERTY(BlueprintReadWrite)
	// 爆擊機率
	int32 criticalP;

	UPROPERTY(BlueprintReadWrite)
	// 爆擊傷害
	float criticalStrike;
	
};

USTRUCT(BlueprintType)
struct FDisciple {

	GENERATED_BODY()

	FDisciple();

	void DecideRarity();

	void ResetRarity(EDiscipleRarityType r);

	void DecideName();

	void DecidePersonality();

	void DecideBackground();

	void DecideLifePalace();

	void DecideStar();

	// 決定屬性
	void DecideAttribute();

	// 設定修煉速度
	void SetCultivateSpeed();

	// 修煉功法
	void CultivateLaw(int32 speed);

	// 修煉境界
	void Practice();

	// 或取下個境界的經驗
	int32 GetNextExp();

	// 可以進階嗎
	bool CanLevelUp();

	// 進階
	void LevelUp();

	// 結婚
	void Marry();
	
	// 離婚
	void Divorce();

	int32 GetDamage();

	void SetEnemy();

	void UseElixirs(FElixirs elixirs);

	UPROPERTY(BlueprintReadWrite)
	// 資質
	EDiscipleRarityType rarity;

	UPROPERTY(BlueprintReadWrite)
	// 性格
	EPersonality personality;

	UPROPERTY(BlueprintReadWrite)
	// 出身背景
	EBackground background;

	UPROPERTY(BlueprintReadWrite)
	// 姓氏
	FText surname;

	UPROPERTY(BlueprintReadWrite)
	// 名字
	FText name;

	//UPROPERTY(BlueprintReadWrite)
	// 根骨
	int32 health = 0;

	//UPROPERTY(BlueprintReadWrite)
	// 攻擊
	int32 attack = 0;

	//UPROPERTY(BlueprintReadWrite)
	// 體魄
	int32 defense = 0;

	UPROPERTY(BlueprintReadWrite)
	// 爆擊機率
	int32 criticalP;

	UPROPERTY(BlueprintReadWrite)
	// 爆擊傷害
	float criticalStrike;

	UPROPERTY(BlueprintReadWrite)
	// 武器
	FEquipment weapon;

	UPROPERTY(BlueprintReadWrite)
	// 法寶
	FEquipment artifact;

	UPROPERTY(BlueprintReadWrite)
	// 暗器
	FEquipment hiddenWeapon;

	UPROPERTY(BlueprintReadWrite)
	// 命宮
	int32 lifePalace;

	UPROPERTY(BlueprintReadWrite)
	// 星辰
	int32 star;

	UPROPERTY(BlueprintReadWrite)
	// 功法
	TArray<FLaw> laws;

	UPROPERTY(BlueprintReadWrite)
	// 修煉速度
	int32 cultivateSpeed = 0;

	UPROPERTY(BlueprintReadWrite)
	// 境界
	int32 level = 0;

	UPROPERTY(BlueprintReadWrite)
	// 境界經驗
	int32 practice = 0;

	UPROPERTY(BlueprintReadWrite)
	// 記錄
	TArray<FText> logs;

	UPROPERTY(BlueprintReadWrite)
	// 年齡
	int32 year;

	// 是否結婚
	bool married = false;

	UPROPERTY(BlueprintReadWrite)
	// 道侶
	FWife wife;

	UPROPERTY(BlueprintReadWrite)
	TMap<FElixirs, int32> usedElixirs;

	UPROPERTY(BlueprintReadWrite)
	// 吃過的丹藥數
	int32 ateElixirs = 0;

	UPROPERTY(BlueprintReadWrite)
	// 一年內吃的丹藥數
	int32 yearAteElixirs = 0;
};