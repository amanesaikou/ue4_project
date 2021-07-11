// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleBattle.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleBattle : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

	static int32 ComputePlayerDamage(USect* sect);

	UFUNCTION(BlueprintCallable)
	static TArray<int32> TwoDisBattle(FDisciple player, FDisciple enemy, int32 playerH, int32 enemyH);
	
};
