// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputeBPLibrary.h"
#include "Constant.h"

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

FString Message::GetEmployDisciple(FString rarity, FString name) {
	TArray<FStringFormatArg> args = {FStringFormatArg(rarity), FStringFormatArg(name)};
	FString str = FString::Format(TEXT("您招收了資質為{0}的{1}。"), args);
	return str;
}

FString Message::GetExpelDisciple(FString rarity, FString name) {
	TArray<FStringFormatArg> args = { FStringFormatArg(rarity), FStringFormatArg(name) };
	FString str = FString::Format(TEXT("您將資質為{0}的{1}逐出了師門。"), args);
	return str;
}

FString Message::GetNewEquipment(FString rarity, FString name, uint8 type) {
	TArray<FString> types = { TEXT("武器"), TEXT("法寶"), TEXT("暗器")};
	TArray<FStringFormatArg> args = {
		FStringFormatArg(rarity), FStringFormatArg(types[type]), FStringFormatArg(name)
	};
	FString str = FString::Format(TEXT("您獲得了{0}{1}{2}。"), args);
	return str;
}

FString Message::GetNewEquipment(FString rarity, FString name, uint8 type, int32 price) {
	TArray<FString> types = { TEXT("武器"), TEXT("法寶"), TEXT("暗器") };
	TArray<FStringFormatArg> args = {
		FStringFormatArg(rarity), FStringFormatArg(types[type]),
		FStringFormatArg(name), FStringFormatArg(price)
	};
	FString str = FString::Format(TEXT("您獲得了{0}{1}{2}，物品欄已滿，獲得了{3}靈石。"), args);
	return str;
}

FString Message::GetNewLaw(FString rarity, FString name, uint8 type) {
	TArray<FString> types = { TEXT("修煉法"), TEXT("鍛體法"), TEXT("武技") };
	TArray<FStringFormatArg> args = {
		FStringFormatArg(rarity), FStringFormatArg(types[type]), FStringFormatArg(name)
	};
	FString str = FString::Format(TEXT("您獲得了{0}{1}{2}。"), args);
	return str;
}

FString Message::GetNewLaw(FString rarity, FString name, uint8 type, int32 price) {
	TArray<FString> types = { TEXT("修煉法"), TEXT("鍛體法"), TEXT("武技") };
	TArray<FStringFormatArg> args = {
		FStringFormatArg(rarity), FStringFormatArg(types[type]),
		FStringFormatArg(name), FStringFormatArg(price)
	};
	FString str = FString::Format(TEXT("您獲得了{0}{1}{2}，物品欄已滿，獲得了{3}靈石。"), args);
	return str;
}

FString Message::GetSellItem(FString rarity, FString name, int32 price, uint8 type, int16 mode) {
	TArray<FString> types;
	switch (mode)
	{
	case 1:	// 裝備
		types = { TEXT("武器"), TEXT("法寶"), TEXT("暗器") };
		break;
	case 2: // 功法
		types = { TEXT("修煉法"), TEXT("鍛體法"), TEXT("武技") };
		break;
	default:
		break;
	}
	TArray<FStringFormatArg> args = {
		FStringFormatArg(rarity), FStringFormatArg(types[type]),
		FStringFormatArg(name), FStringFormatArg(price)
	};
	FString str = FString::Format(TEXT("您出售{0}{1}{2}，獲得了{3}靈石。"), args);
	return str;
}

FString Message::GetSellSpiritBeast(FString name, int32 price) {
	TArray<FStringFormatArg> args = { FStringFormatArg(name), FStringFormatArg(price) };
	FString str = FString::Format(TEXT("您出售{0}，獲得了{1}靈石。"), args);
	return str;
}

FString Message::GetFacilityLevelUp(FString name, int32 lv, const int32 cost) {
	TArray<FStringFormatArg> args = {
		FStringFormatArg(cost), FStringFormatArg(name), FStringFormatArg(lv)
	};
	FString str = FString::Format(TEXT("您花費{0}靈石，將{1}提升至{2}等。"), args);
	return str;
}

int32 UConstantBPLibrary::GetDiscipleLimit() {
	return gDiscipleLimit;
}

int32 UConstantBPLibrary::GetItemLimit() {
	return gItemLimit;
}

int32 UConstantBPLibrary::GetEnhanceLimit() {
	return gEnhanceLimit;
}

int32 UConstantBPLibrary::GetRefineLimit() {
	return gRefineLimit;
}

int32 UConstantBPLibrary::GetLawLevelLimit() {
	return gLawLevelLimit;
}
