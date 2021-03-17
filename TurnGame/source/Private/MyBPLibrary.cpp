// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBPLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/Paths.h"

// UE_LOG(LogTemp, Warning, TEXT("Path is %s"), *filePath);

int GetRandomInt(int min, int max) {
	return FMath::RandRange(min, max);
}

void* DLLHandle = NULL;

typedef int(*DLLGetProperty)(int value, int rarity, int random);
DLLGetProperty GetProperty = NULL;

typedef float(*DLLGetDamage)(float sourceAttack, float sourceCS, float targetDefense, float random);
DLLGetDamage GetDamage = NULL;


void UMyBPLibrary::ImportDLL() {
	if (DLLHandle == NULL) {
		FString filePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("testdll/"), TEXT("Dll1.dll"));
		if (FPaths::FileExists(*filePath)) {
			DLLHandle = FPlatformProcess::GetDllHandle(*filePath);
			UE_LOG(LogTemp, Warning, TEXT("DLL is loading..."));
		}
	}
}

int UMyBPLibrary::ComputeProperty(int value, uint8& rarity, int& max) {

	UMyBPLibrary::ImportDLL();

	if (GetProperty == NULL) {
		FString procName = "DllLib::GetProperty";
		GetProperty = (DLLGetProperty)FPlatformProcess::GetDllExport(DLLHandle, *procName);
	}

	return GetProperty(value, int(rarity), GetRandomInt(0, max));
}

float UMyBPLibrary::ComputeDamage(float sourceAttack, float sourceCS, float targetDefense, int baseDamage) {

	UMyBPLibrary::ImportDLL();

	if (GetDamage == NULL) {
		FString procName = "DllLib::GetDamage";
		GetDamage = (DLLGetDamage)FPlatformProcess::GetDllExport(DLLHandle, *procName);
	}

	return GetDamage(sourceAttack, sourceCS, targetDefense, FMath::FRandRange(0.0, 100.0)) + baseDamage;
}

void UMyBPLibrary::FreeDLL() {
	if (DLLHandle != NULL) {
		FPlatformProcess::FreeDllHandle(DLLHandle);
		DLLHandle = NULL;
		GetProperty = NULL;
		GetDamage = NULL;
	}
}