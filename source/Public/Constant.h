// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Constant.generated.h"


/**
 * 
 */

void SetYear(int32 y);

void AfterAYear();
int32 GetNowYear();

 // 武器路徑表
TArray<FString> GetWeaponPath();

// 法寶路徑表
TArray<FString> GetArtifactPath();

// 暗器路徑表
TArray<FString> GetHiddenWeaponPath();

const char* GetDiscipleNamePath(int32 choice);

constexpr int32 gCostMax = 100000000;