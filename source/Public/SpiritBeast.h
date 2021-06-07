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

	// «Øºc¤l
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

// ÆFÃ~
UCLASS(BlueprintType)
class DEVELOP_API USpiritBeast : public UObject {
	GENERATED_BODY()

public:
	USpiritBeast();

	void DecideContent();

	void DecidePassiveSkill();

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	FPassiveSkill GetPassiveSkill() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyDefense() const;

	int32 WhichPassiveSkill(int32 index) const;

private:
	FCommonAttribute attribute;

	FPassiveSkill passiveSkill;

	int32 star;

	int32 blood;

	int32 grade;
};
