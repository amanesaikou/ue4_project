// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ComputeBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOP_API UComputeBPLibrary : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static float GetRemainingPercent(int32 original, int32 after);

	UFUNCTION(BlueprintCallable)
	static int32 GetRemainingHealth(int32 targetAttack, int32 sourceHealth, int32 sourceDefense);

};
