// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyBPLibrary.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

/**
 * 
 */

// �@�q�ݩ�
// �׭^�̤l �˳� ���D�����O�ϥ�
USTRUCT(BlueprintType)
struct FCommonAttribute : public FTableRowBase {

	GENERATED_BODY()

	// �غc�l
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
	
	// �W��
	UPROPERTY(BlueprintReadWrite)
	FString name;

	// �����O
	UPROPERTY(BlueprintReadWrite)
	int32 attack;

	// ��q
	UPROPERTY(BlueprintReadWrite)
	int32 health;

	// ���m
	UPROPERTY(BlueprintReadWrite)
	int32 defense;

};

// ���~����
UCLASS()
class DEVELOP_API UItem : public UObject {

	GENERATED_BODY()

public:
	UItem();

	int32 GetID() const;

	// ���~�}����
	EItemRarityType rarity;

	UFUNCTION(BlueprintCallable)
	int32 GetPrice() const;

	UFUNCTION(BlueprintCallable)
	FString GetRarityName() const;

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

protected:
	// ���~�ݩ�
	UPROPERTY(BlueprintReadWrite)
	FCommonAttribute attribute;

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

	// �T�w�O���ظ˳�
	void DecideType();

	UFUNCTION(BlueprintCallable)
	// ����˳ƫ��A
	EEquipmentType GetType() const;

	// �ھڸ˳Ƶ}���׻P����Ū��
	void DecideContent();

	UFUNCTION(BlueprintCallable)
	// �˳Ʊj��
	bool Enhance(const int32& spiritStone);

	// �i�H�j�ƶ�
	bool CanEnhance(const int32& spiritStone, int32 cost);

	UFUNCTION(BlueprintCallable)
	// ����j�ƶO��
	int32 GetEnhancementCost() const;

	UFUNCTION(BlueprintCallable)
	// �˳ƺ��
	bool Refine(const int32& spiritStone);

	// �i�H��Ҷ�
	bool CanRefine(const int32& spiritStone, int32 cost);

	UFUNCTION(BlueprintCallable)
	// �����ҶO��
	int32 GetRefiningCost() const;

	UFUNCTION(BlueprintCallable)
	// ����j�Ƶ���
	int32 GetEnhancementLevel() const;

	UFUNCTION(BlueprintCallable)
	// �����ҵ���
	int32 GetRefiningLevel() const;

	UFUNCTION(BlueprintCallable)
	// ����̲ק���
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	// ����̲ץͩR
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	// ����̲ר��m
	int32 GetFinallyDefense() const;
	
	// �j�Ƶ��ŻP��ҵ��Ū��[���ۭ�
	float GetBuff() const;

private:
	EEquipmentType equipmentType;

	// �j�Ƶ���
	int32 enhancementLevel;

	// ��ҵ���
	int32 refiningLevel;
};

// �׽m�k
UCLASS(BlueprintType)
class DEVELOP_API UCultivationLaw : public UItem {

	GENERATED_BODY()

public:
	UCultivationLaw();

	// �T�w�O���إ\�k
	void DecideType();

	// �ھڥ\�k�}���׻P����Ū���ܥ\�k
	void DecideLaw();

	// �׽m�\�k
	UFUNCTION(BlueprintCallable)
	bool LevelUp(const int32& spiritStone);

	// �i�H�׽m��?
	bool CanLevelUp(const int32& spiritStone, int32 cost);

	UFUNCTION(BlueprintCallable)
	int32 GetLevel() const;

	void SetLevelZero();

	UFUNCTION(BlueprintCallable)
	// ����\�k�׽m�h��
	FString GetLevelName() const;

	UFUNCTION(BlueprintCallable)
	// ����\�k�׷��F�۪�O
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
	// �׽m�k����
	ECultivationType cultivationType;

	// �צ浥��
	int32 lawLevel;
};