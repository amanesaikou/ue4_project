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

	// 決定弟子資質
	void DecideRarity();

	// 決定弟子命宮數量
	void DecideLifePalace();

	// 決定弟子星辰數量
	void DecideStar();

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	// 獲取資質
	UFUNCTION(BlueprintCallable)
	EDiscipleRarityType GetRarity() const;
	
	// 獲取資質名稱
	UFUNCTION(BlueprintCallable)
	FString GetRarityName() const;

	UFUNCTION(BlueprintCallable)
	//
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	//
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	//
	int32 GetFinallyDefense() const;

	// 命宮與星辰加成
	float GetBuff() const;

	// 穿裝備
	UFUNCTION(BlueprintCallable)
	void WearEquipment(const TArray<UEquipment*>& weapons, int32 index);
	void WearWeapon(const TArray<UEquipment*>& weapons, int32 index);
	void WearArtifact(const TArray<UEquipment*>& artifacts, int32 index);
	void WearHiddenWeapon(const TArray<UEquipment*>& hiddenWeapons, int32 index);

	// 使用功法
	UFUNCTION(BlueprintCallable)
	void UseLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	void UseCultivationLaw(const TArray<UCultivationLaw*>& laws, int32 index);
	void UseWorkoutLaw(const TArray<UCultivationLaw*>& laws, int32 index);
	void UseAttackSkill(const TArray<UCultivationLaw*>& laws, int32 index);

	void RemoveAll();

	UFUNCTION(BlueprintCallable)
	void RemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	void RemoveLaw(UCultivationLaw* law);

	class UMyGameInstance* GetGameInstance() const;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetArtifact() const;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetHiddenWeapon() const;

	UFUNCTION(BlueprintCallable)
	UCultivationLaw* GetCultivationLaw() const;

	UFUNCTION(BlueprintCallable)
	UCultivationLaw* GetWorkoutLaw() const;

	UFUNCTION(BlueprintCallable)
	UCultivationLaw* GetAttackSkill() const;

	UFUNCTION(BlueprintCallable)
	int32 GetLifePalace() const;

	UFUNCTION(BlueprintCallable)
	FString GetLifePalaceTitle() const;

	UFUNCTION(BlueprintCallable)
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
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

//template void UEliteDisciple::Apply(const TArray<UEquipment*>& items, int32 index, UEquipment* item);
//template void UEliteDisciple::Apply(const TArray<UCultivationLaw*>& items, int32 index, UCultivationLaw* item);