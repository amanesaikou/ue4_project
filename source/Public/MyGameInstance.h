// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "slua.h"
#include "Sect.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOP_API UMyGameInstance : public UGameInstance {

	GENERATED_BODY()

public:
	UMyGameInstance();

	void CreateEnemys();

	UFUNCTION(BlueprintCallable)
	USect* GetSect();

	UFUNCTION(BlueprintCallable)
	TArray<FCommonAttribute> GetEnemys();

	UFUNCTION(BlueprintCallable)
	void SetEnemyIndex(int32 index);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyIndex();

	UFUNCTION(BlueprintCallable)
	FCommonAttribute GetEnemy();

	UFUNCTION(BlueprintCallable)
	void AfterAYear();

	UFUNCTION(BlueprintCallable)
	int32 GetYears() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USect* sect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCommonAttribute> enemys;

	int32 enemyIndex = 0;

	int32 years = 1;
};
	
