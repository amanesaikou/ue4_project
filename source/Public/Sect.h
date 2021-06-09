// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "SpiritBeast.h"
#include "Facility.h"
#include <functional> // std::functional
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

	void SetFacility();

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
	// 加回弟子脫下的裝備或加入新的裝備
	void AddRemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// 可以加入裝備嗎
	bool CanAddEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// 加入新的功法
	void AddLaw();

	UFUNCTION(BlueprintCallable)
	//加入新的靈獸
	void AddSpiritBeast();

	UFUNCTION(BlueprintCallable)
	// 加回弟子放棄修練的功法或加入新的功法
	void AddRemoveLaw(UCultivationLaw* law);

	UFUNCTION(BlueprintCallable)
	// 可以加入功法嗎
	bool CanAddLaw(UCultivationLaw* law);

	UFUNCTION(BlueprintCallable)
	// 獲取所有設施
	TArray<FFacility> GetFacilities();

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
	// 獲取所有靈獸
	TArray<USpiritBeast*> GetSpiritBeasts();

	UFUNCTION(BlueprintCallable)
	// 移除裝備
	void RemoveEquipment(UEquipment* equipment, int32 index);

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

	void AddAttribute(int32& attribute, std::function<int32(UEliteDisciple*)> Get);

	UFUNCTION(BlueprintCallable)
	// 獲取最終攻擊
	int32 GetFinallyAttack();

	UFUNCTION(BlueprintCallable)
	// 獲取最終生命
	int32 GetFinallyHealth();

	UFUNCTION(BlueprintCallable)
	// 獲取最終防禦
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

	UFUNCTION(BlueprintCallable)
	// 獲取靈石
	int32 GetSpiritStone() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 弟子
	TArray<UEliteDisciple*> eliteDisciples;

	// uobject建立名稱數字
	int32 eliteDiscipleNums = 0;
	int32 equipmentNums = 0;
	int32 lawNums = 0;
	int32 spiritBeastNums = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 靈石
	int32 spiritStone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 藥材
	int32 medicinalMaterials;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 武器
	TArray<UEquipment*> weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 法寶
	TArray<UEquipment*> artifacts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 暗器
	TArray<UEquipment*> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 修練法
	TArray<UCultivationLaw*> cultivationLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 鍛體法
	TArray<UCultivationLaw*> workoutLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 武技
	TArray<UCultivationLaw*> attackSkills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 靈獸
	TArray<USpiritBeast*> spiritBeasts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 設施
	TArray<FFacility> facilities;

};

//void AddAttribute(int32& attribute, int32 start, int32 end, TArray<UEliteDisciple*>& disciples, std::function<int32(UEliteDisciple*)> Get);
