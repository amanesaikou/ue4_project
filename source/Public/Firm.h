// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "SpiritBeast.h"
#include "Firm.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOP_API UFirm : public UObject {
	GENERATED_BODY()

public:
	UFirm();

	void UpdateGoods();

	void AddEquipment();

	void AddLaw();

	void AddSpiritBeast();

	UFUNCTION(BlueprintCallable)
	TArray<UEquipment*> GetEquipments();

	void RemoveEquipment(int32 index);

	void RemoveLaw(int32 index);

	void RemoveSpiritBeast(int32 index);

	UFUNCTION(BlueprintCallable)
	TArray<UCultivationLaw*> GetLaws();

	UFUNCTION(BlueprintCallable)
	TArray<USpiritBeast*> GetSpiritBeasts();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 出售的裝備
	TArray<UEquipment*> equipments;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 出售的功法
	TArray<UCultivationLaw*> laws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 出售的靈獸
	TArray<USpiritBeast*> spiritBeasts;


private:
	int32 eNum = 0;
	int32 lNum = 0;
	int32 sNum = 0;
	
};
