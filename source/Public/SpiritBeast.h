// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyBPLibrary.h"
#include "Item.h"
#include "SpiritBeast.generated.h"

/**
 * 
 */


 // 
USTRUCT(BlueprintType)
struct FPassiveSkill : public FTableRowBase {

	GENERATED_BODY()

	// �غc�l
	FPassiveSkill();

	EPassiveSkill GetPassiveSkill() const;

	FString GetName() const;

	int32 GetValue() const;

	UPROPERTY(BlueprintReadWrite)
	EPassiveSkill type;

	UPROPERTY(BlueprintReadWrite)
	FString name;

	UPROPERTY(BlueprintReadWrite)
	int32 value;
};

// �F�~
UCLASS(BlueprintType)
class DEVELOP_API USpiritBeast : public UObject {
	GENERATED_BODY()

public:
	USpiritBeast();

	void DecideContent();

	void DecidePassiveSkill();

	// �]�w����
	void DecideClass();

	// �M�w�P��
	void DecideStar();

	// �M�w�~��
	void DecideGrade();

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBlood() const;

	UFUNCTION(BlueprintCallable)
	int32 GetGrade() const;

	UFUNCTION(BlueprintCallable)
	FPassiveSkill GetPassiveSkill() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyDefense() const;

	float GetBuff() const;

	// ����ѽ�[��
	int32 WhichPassiveSkill(int32 index) const;

private:
	// �ݩ�
	FCommonAttribute attribute;

	// �ѽ�
	FPassiveSkill passiveSkill;

	// �P��
	int32 star;

	// ��߿@��
	int32 blood;

	// �~��
	int32 grade;
};
