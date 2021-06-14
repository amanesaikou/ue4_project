// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "Disciple.generated.h"

/**
 * 
 */

// 菁英弟子
UCLASS(BlueprintType)
class DEVELOP_API UEliteDisciple : public UObject {

	GENERATED_BODY()

public:

	UEliteDisciple();

	// 設定弟子姓名 須修改
	void DecideName();

	// 獲取弟子的姓氏與名字進行組合
	FString GetName(const char* path) const;

	// 設定弟子頭像索引值
	void SetImageIndex();

	UFUNCTION(BlueprintCallable)
	// 獲取弟子頭像索引值
	int32 GetImageIndex() const;

	// 決定弟子資質
	void DecideRarity();

	// 決定弟子命宮數量
	void DecideLifePalace();

	// 決定弟子星辰數量
	void DecideStar();

	UFUNCTION(BlueprintCallable)
	// 獲取弟子名稱
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	// 獲取資質
	EDiscipleRarityType GetRarity() const;
	
	UFUNCTION(BlueprintCallable)
	// 獲取資質名稱
	FString GetRarityName() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終攻擊
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終生命
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	// 獲取最終防禦
	int32 GetFinallyDefense() const;

	// 命宮與星辰加成
	float GetBuff() const;

	UFUNCTION(BlueprintCallable)
	// 穿裝備
	void WearEquipment(const TArray<UEquipment*>& weapons, int32 index);

	// 穿武器
	void WearWeapon(const TArray<UEquipment*>& weapons, int32 index);

	// 穿法寶
	void WearArtifact(const TArray<UEquipment*>& artifacts, int32 index);

	// 穿暗器
	void WearHiddenWeapon(const TArray<UEquipment*>& hiddenWeapons, int32 index);

	// 修練功法
	UFUNCTION(BlueprintCallable)
	void UseLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	// 修練修練法
	void UseCultivationLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	// 修練鍛體法
	void UseWorkoutLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	// 修練武技
	void UseAttackSkill(const TArray<UCultivationLaw*>& laws, int32 index);

	// 移除全部裝備與功法
	void RemoveAll();

	UFUNCTION(BlueprintCallable)
	// 脫下裝備
	void RemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// 放棄修練
	void RemoveLaw(UCultivationLaw* law);

	// 獲取GameInstance
	class UMyGameInstance* GetGameInstance() const;

	UFUNCTION(BlueprintCallable)
	// 取得武器
	UEquipment* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	// 取得法寶
	UEquipment* GetArtifact() const;

	UFUNCTION(BlueprintCallable)
	// 取得暗器
	UEquipment* GetHiddenWeapon() const;

	UFUNCTION(BlueprintCallable)
	// 取得修練法
	UCultivationLaw* GetCultivationLaw() const;

	UFUNCTION(BlueprintCallable)
	// 取得鍛體法
	UCultivationLaw* GetWorkoutLaw() const;

	UFUNCTION(BlueprintCallable)
	// 取得武技
	UCultivationLaw* GetAttackSkill() const;

	UFUNCTION(BlueprintCallable)
	// 獲取命宮數量
	int32 GetLifePalace() const;

	UFUNCTION(BlueprintCallable)
	// 獲取命宮稱號
	FString GetLifePalaceTitle() const;

	UFUNCTION(BlueprintCallable)
	// 獲取星辰數量
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
	// 獲取星辰稱號
	FString GetStarTitle() const;

	// 弟子資質
	EDiscipleRarityType rarity;

protected:

	// 菁英弟子基本屬性 
	FCommonAttribute attriute;

	// 三件裝備
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UEquipment* weapon;			// 武器
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UEquipment* artifact;		// 法寶
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UEquipment* hiddenWeapon;	// 暗器

	// 三種功法
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* cultivationLaw; // 心法
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* workoutLaw;	 // 鍛體法
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* attackSkill;	 // 武技

	// 命宮數 最多13
	int32 lifePalace;

	// 星辰數 最多9
	int32 stars;

};
