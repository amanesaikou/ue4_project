// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "Sect.generated.h"

/**
 * 
 */

// 門派
UCLASS(BlueprintType)
class DEVELOP_API USect : public UObject {
	GENERATED_BODY()

public:

	// 建構子
	USect();

	UFUNCTION(BlueprintCallable)
	// 加入新的弟子
	void AddEliteDisciple();

	UFUNCTION(BlueprintCallable)
	// 招募弟子
	void EmployEliteDisciple();

	UFUNCTION(BlueprintCallable)
	// 可以招募嗎
	bool CanEmployDisciple();

	UFUNCTION(BlueprintCallable)
	// 驅逐弟子
	void ExpelDisciple(int32 index);

	UFUNCTION(BlueprintCallable)
	// 可以驅逐弟子嗎 驅逐弟子後物品會加回來 須檢查是否超過物品數量上限 
	bool CanExpelDisciple(int32 index);

	UFUNCTION(BlueprintCallable)
	// 加入新的裝備
	void AddEquipment();

	UFUNCTION(BlueprintCallable)
	// 加回弟子脫下的裝備
	void AddRemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	bool CanAddEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// 加入新的功法
	void AddLaw();

	UFUNCTION(BlueprintCallable)
	// 加回弟子脫下的功法
	void AddRemoveLaw(UCultivationLaw* law);

	UFUNCTION(BlueprintCallable)
	// 獲取所有弟子
	TArray<UEliteDisciple*> GetEliteDisciples();

	UFUNCTION(BlueprintCallable)
	// 獲取所有武器
	TArray<UEquipment*> GetWeapons();

	UFUNCTION(BlueprintCallable)
	// 獲取所有法寶
	TArray<UEquipment*> GetArtifacts();

	UFUNCTION(BlueprintCallable)
	// 獲取所有暗器
	TArray<UEquipment*> GetHiddenWeapons();

	UFUNCTION(BlueprintCallable)
	// 獲取所有修練法
	TArray<UCultivationLaw*> GetCultivationLaws();

	UFUNCTION(BlueprintCallable)
	// 獲取所有緞體法
	TArray<UCultivationLaw*> GetWorkoutLaws();

	UFUNCTION(BlueprintCallable)
	// 獲取所有武技
	TArray<UCultivationLaw*> GetAttackSkills();

	UFUNCTION(BlueprintCallable)
	// 移除武器
	void RemoveWeapon(int32 index);

	UFUNCTION(BlueprintCallable)
	// 移除法寶
	void RemoveArtifact(int32 index);

	UFUNCTION(BlueprintCallable)
	// 移除暗器
	void RemoveHiddenWeapon(int32 index);

	UFUNCTION(BlueprintCallable)
	// 移除修練法
	void RemoveCultivationLaw(int32 index);

	UFUNCTION(BlueprintCallable)
	// 移除鍛體法
	void RemoveWorkoutLaw(int32 index);

	UFUNCTION(BlueprintCallable)
	// 移除武技
	void RemoveAttackSkill(int32 index);

	UFUNCTION(BlueprintCallable)
	// 使用靈石
	void UseSpiritStone(int32 cost);

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyAttack();

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyHealth();

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyDefense();

	UFUNCTION(BlueprintCallable)
	// 弟子排序
	void DiscipleSort();

	UFUNCTION(BlueprintCallable)
	// 功法排序
	void CultivationLawSort(int32 index);

	UFUNCTION(BlueprintCallable)
	// 裝備排序
	void EquipmentSort(int32 index);

	UFUNCTION(BlueprintCallable)
	// 增加靈石
	void AddSpiritStone(int32 num);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEliteDisciple*> eliteDisciples;

	// uobject建立名稱數字
	int32 eliteDiscipleNums = 0;
	int32 equipmentNums = 0;
	int32 lawNums = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 money;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 spiritStone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEquipment*> weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEquipment*> artifacts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEquipment*> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> cultivationLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> workoutLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> attackSkills;

};
