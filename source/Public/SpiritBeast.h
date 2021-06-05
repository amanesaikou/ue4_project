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

	FString GetContent() const;

	EPassiveSkill type;

	FString name;

	int32 value;

	FString content;

};

// ÆFÃ~
UCLASS(BlueprintType)
class DEVELOP_API USpiritBeast : public UObject {
	GENERATED_BODY()

public:
	USpiritBeast();

	void DecideContent();

	UFUNCTION(BlueprintCallable)
	FString GetName();

private:
	FCommonAttribute attribute;

	FPassiveSkill passiveSkill;

	int32 star;

	int32 blood;

	int32 grade;
};
