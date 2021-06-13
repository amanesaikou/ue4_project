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

int32 UComputeBPLibrary::CheckOverRange(int32 value, int32 limit) {
	return value > limit ? limit : value;
}

int32 UComputeBPLibrary::From64To32(int64 value) {
	return int32(value);
}

FString Message::GetEmployDisciple(FString rarity, FString name) {
	FString str = TEXT("您招收了資質為");
	str += rarity;
	str += TEXT("的");
	str += name;
	str += TEXT("。");
	return str;
}

FString Message::GetNewEquipment(FString rarity, FString name, uint8 type) {
	TArray<FString> types = { TEXT("武器"), TEXT("法寶"), TEXT("暗器")};
	FString str = TEXT("您獲得了");
	str += rarity;
	str += types[type];
	str += name;
	str += TEXT("。");
	return str;
}

FString Message::GetNewEquipment(FString rarity, FString name, uint8 type, int32 price) {
	TArray<FString> types = { TEXT("武器"), TEXT("法寶"), TEXT("暗器") };
	FString str = TEXT("您獲得了");
	str += rarity;
	str += types[type];
	str += name;
	str += TEXT("，物品欄已滿，您獲得了");
	str += FString::FromInt(price);
	str += TEXT("靈石。");
	return str;
}

FString Message::GetNewLaw(FString rarity, FString name, uint8 type) {
	TArray<FString> types = { TEXT("修煉法"), TEXT("鍛體法"), TEXT("武技") };
	FString str = TEXT("您獲得了");
	str += rarity;
	str += types[type];
	str += name;
	str += TEXT("。");
	return str;
}

FString Message::GetNewLaw(FString rarity, FString name, uint8 type, int32 price) {
	TArray<FString> types = { TEXT("修煉法"), TEXT("鍛體法"), TEXT("武技") };
	FString str = TEXT("您獲得了");
	str += rarity;
	str += types[type];
	str += name;
	str += TEXT("，物品欄已滿，你獲得了");
	str += FString::FromInt(price);
	str += TEXT("靈石。");
	return str;
}

FString Message::GetFacilityLevelUp(FString name, int32 lv, int32 cost) {
	FString str = TEXT("您花費");
	str += FString::FromInt(cost);
	str += TEXT("靈石，將");
	str += name;
	str += TEXT("提升至");
	str += FString::FromInt(lv);
	str += TEXT("等。");
	return str;
}

