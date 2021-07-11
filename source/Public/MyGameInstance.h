// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sect.h"
#include "EnemySect.h"
#include "MyGameInstance.generated.h"


/**
 * 
 */

UCLASS()
class DEVELOPVER1_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	UMyGameInstance();

	UFUNCTION(BlueprintCallable)
	void AfterYear();

	UFUNCTION(BlueprintCallable)
	int32 GetYear();

	UFUNCTION(BlueprintCallable)
	UEnemySect* GetEnemy(int32 index);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USect* sect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 min = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEnemySect*> enemys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 enemyIndex = 0;
};
