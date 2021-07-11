// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "Facility.h"
#include "SpiritBeast.h"
#include "Shop.h"
#include "Async/AsyncWork.h"
#include "Sect.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTreasure : public FTableRowBase {
	GENERATED_BODY()
	FTreasure() {};
	UPROPERTY(BlueprintReadWrite)
	int32 id;
	UPROPERTY(BlueprintReadWrite)
	FText name;
	UPROPERTY(BlueprintReadWrite)
	FText content;
	UPROPERTY(BlueprintReadWrite)
	FText effect;
	UPROPERTY(BlueprintReadWrite)
	ESectValue type;
	UPROPERTY(BlueprintReadWrite)
	int32 value;
};

UCLASS(BlueprintType)
class DEVELOPVER1_API USect : public UObject {
	GENERATED_BODY()
public:
	USect();

	void ReadLaws();

	void ReadTreasures();

	void ReadFacility();

	void ReadElixirs();

	UFUNCTION(BlueprintCallable)
	void AddTreasure(FTreasure& t);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetFiveDisIndex();

	UFUNCTION(BlueprintCallable)
	TArray<FDisciple> GetFiveDis(TArray<int32> index);

	UFUNCTION(BlueprintCallable)
	TArray<FText> Explore();

	void Update();

	void Cultivate();

	void AddSpiritStone(int32 num);

	UFUNCTION(BlueprintCallable)
	TMap<FElixirs, int32> MakeElixirs(int32 num);

	UPROPERTY(BlueprintReadWrite)
	TArray<FDisciple> disciples;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> weapons;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> artifacts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> hadLaws;

	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> noGetLaws;

	UPROPERTY(BlueprintReadWrite)
	TArray<FSpiritBeast> spiritBeasts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTreasure> hadTreasure;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTreasure> noGetTreasures;

	UPROPERTY(BlueprintReadWrite)
	TArray<FFacility> facilities;

	UPROPERTY(BlueprintReadWrite)
	TMap<FElixirs, int32> elixirs;

	UPROPERTY(BlueprintReadWrite)
	int32 spiritStone = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 medicinalMaterials = 0;

	// 每年靈石收入
	int32 ySpiritStone = 0;
	// 每年藥材收入
	int32 yMedicinalMaterials = 0;
	//
	int32 health = 0;
	int32 attack = 0;
	int32 defense = 0;
	int32 speed = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 level = 10;

	UPROPERTY(BlueprintReadWrite)
	FShop shop;
};

class SectAsyncTask : public FNonAbandonableTask {
	friend class FAsyncTask<SectAsyncTask>;

	USect* sect;

	SectAsyncTask(USect* temp) : sect(temp) { }

	void DoWork() {
		int32 index = 0;
		for (auto& i : sect->spiritBeasts) {
			i.Growth();
			if (i.IsDeath())
				sect->spiritBeasts.RemoveAt(index);
			else
				++index;
		}
	}

	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(ExampleAsyncTask, STATGROUP_ThreadPoolAsyncTasks); }
};