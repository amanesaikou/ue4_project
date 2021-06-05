// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputeBPLibrary.h"

float UComputeBPLibrary::GetRemainingPercent(int32 original, int32 after) {
	return float(after) / float(original);
}

int32 UComputeBPLibrary::GetRemainingHealth(int32 targetAttack, int32 sourceHealth, int32 sourceDefense) {
	int32 random = FMath::RandRange(1, 100);
	int32 remainingHealth = 0;
	if (random < 31) {
		if (targetAttack * 1.3 - sourceDefense * 1.1 <= 10000)
			remainingHealth = sourceHealth - 10000;
		else
			remainingHealth = sourceHealth - (targetAttack * 1.3 - sourceDefense * 1.1);
	}
	else {
		if(targetAttack - sourceDefense * 1.1 <= 10000)
			remainingHealth = sourceHealth - 10000;
		else
			remainingHealth = sourceHealth - (targetAttack - sourceDefense * 1.1);
	}

	if (remainingHealth <= 0)
		return 0;
	else
		return remainingHealth;
}
