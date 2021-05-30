// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Math/Color.h"
#include "MyBPLibrary.generated.h"

// 修練法種類
UENUM(BlueprintType)
enum class ECultivationType : uint8 {
	CultivationLaw	= 0,	// 心法
	WorkoutLaw		= 1,	// 鍛體法
	AttackSkill		= 2,	// 武技
};

// 裝備種類
UENUM(BlueprintType)
enum class EEquipmentType : uint8 {
	Weapon			= 0,	// 武器
	Artifact		= 1,	// 法寶
	HiddenWeapon	= 2,	// 暗器
};

// 道具稀有度
UENUM(BlueprintType)
enum class EItemRarityType : uint8 {
	Immortal		= 0, // 仙級		1%
	Holy			= 1, // 聖級		3%
	Sky				= 2, // 天級		5%
	Earth			= 3, // 地級		8%
	Mysterious		= 4, // 玄級		14%
	Yellow			= 5, // 黃級		24%
	Human			= 6, // 人級		45%
};

// 弟子稀有度
UENUM(BlueprintType)
enum class EDiscipleRarityType : uint8 {
	SonofEra		= 0,	// 紀元之子	1%
	Genius			= 1,	// 天驕		4%
	Extraordinary	= 2,	// 非凡		9%
	Outstanding		= 3,	// 傑出		12%
	Excellent		= 4,	// 優秀		26%
	Normal			= 5,	// 一般		48%
};

// 共用資料結構
USTRUCT(BlueprintType)
struct FCommonData : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FCommonData();

	// 功法層次 物品稀有度等
	UPROPERTY(BlueprintReadWrite)
	FString name;

	// 修練靈石花費 物品稀有度機率等
	UPROPERTY(BlueprintReadWrite)
	int32 number;

	FString GetName() const;

	int32 GetNumber() const;

};

// 物品表資料
USTRUCT(BlueprintType)
struct FDataTablePath : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FDataTablePath();

	// 檔案路徑
	UPROPERTY(BlueprintReadWrite)
	FString tablePath;

	const char* GetPath() const;

};

// 各種字串資料結構
USTRUCT(BlueprintType)
struct FCommonString : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FCommonString();

	// 
	UPROPERTY(BlueprintReadWrite)
	FString str;

	FString GetString() const;

};

/**
 * 
 */
 // 處理各個enum的類別
UCLASS()
class DEVELOP_API UTypeBPLibrary : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:
	// 決定物品稀有度與弟子資質的模板
	template<class T>
	static T DecideRarity(const char* tablePath);

	// 根據機率獲取對應的稀有度
	static uint8 GetRarityIndex(TArray<int32>& probabilities);

	// 決定修煉法與裝備種類的模板
	template<class T>
	static T DecideType();

	// 獲取物品稀有度或弟子資質的名稱的模板
	template<class T>
	static FString GetRarityName(const char* tablePath, T rarity);

	UFUNCTION(BlueprintCallable)
	static FLinearColor GetDiscipleColor(EDiscipleRarityType rarity);

	static bool IsSonofEra(EDiscipleRarityType rarity);
	static bool IsGenius(EDiscipleRarityType rarity);
	static bool IsExtraordinary(EDiscipleRarityType rarity);
	static bool IsOutstanding(EDiscipleRarityType rarity);
	static bool IsExcellent(EDiscipleRarityType rarity);
	static bool IsNormal(EDiscipleRarityType rarity);
	/*
	static bool IsImmortal(EItemRarityType rarity);
	static bool IsHoly(EItemRarityType rarity);
	static bool IsSky(EItemRarityType rarity);
	static bool IsEarth(EItemRarityType rarity);
	static bool IsImmortal(EItemRarityType rarity);
	static bool IsImmortal(EItemRarityType rarity);
	static bool IsImmortal(EItemRarityType rarity);
	*/
};

// 資料集函式庫
//UCLASS()
class DEVELOP_API UDatasetBPLibrary {//: public UBlueprintFunctionLibrary {

	//GENERATED_BODY()

public:
	// 獲取機率 物品稀有度 弟子資質等
	static TArray<int32> GetRarityProbability(const char* tablePath);

	// 獲取資料表路徑
	static const char* GetTablePath(const char* path, int32 index);
	//
	static FName FromIntToFName(int32 num);
};

class DEVELOP_API UPath {

public:
	// 功法層次表的路徑
	static const char* GetLawLevelPath();

	// 物品稀有度表路徑
	static const char* GetItemRarityPath();

	// 弟子資質表路徑
	static const char* GetDiscipleRarityPath();

	// 功法屬性路徑表
	static const char* GetLawTablePath();

	// 裝備屬性路徑表
	static const char* GetEquipmentTablePath();

	// 裝備屬性路徑表
	static const char* GetLifePalaceTitlePath();

	// 裝備屬性路徑表
	static const char* GetStarTitlePath();
};

// 實例化
//template FString UTypeBPLibrary::GetRarityName(const char* tablePath, int32 rarity);
template FString UTypeBPLibrary::GetRarityName(const char* tablePath, EItemRarityType rarity);
template FString UTypeBPLibrary::GetRarityName(const char* tablePath, EDiscipleRarityType rarity);

template int32 UTypeBPLibrary::DecideRarity(const char* tablePath);
template EItemRarityType UTypeBPLibrary::DecideRarity(const char* tablePath);
template EDiscipleRarityType UTypeBPLibrary::DecideRarity(const char* tablePath);

template ECultivationType UTypeBPLibrary::DecideType();
template EEquipmentType UTypeBPLibrary::DecideType();