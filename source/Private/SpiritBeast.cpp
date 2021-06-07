// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiritBeast.h"
#include "Constant.h"

FPassiveSkill::FPassiveSkill() {

}

EPassiveSkill FPassiveSkill::GetPassiveSkill() const {
	return type;
}

FString FPassiveSkill::GetName() const {
	return name;
}

int32 FPassiveSkill::GetValue() const {
	return value;
}

USpiritBeast::USpiritBeast() {
	DecideContent();
	DecidePassiveSkill();
}

void USpiritBeast::DecideContent() {
	const char* path = gSpiritBeast;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	int32 random = FMath::RandRange(0, rowNames.Num() - 1);
	FCommonAttribute* temp = pDataTable->FindRow<FCommonAttribute>(UDatasetBPLibrary::FromIntToFName(random), "");
	attribute = *temp;
}

void USpiritBeast::DecidePassiveSkill() {
	const char* path = gPassiveSkill;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	int32 random = FMath::RandRange(0, rowNames.Num() - 1);
	FPassiveSkill* temp = pDataTable->FindRow<FPassiveSkill>(UDatasetBPLibrary::FromIntToFName(random), "");
	passiveSkill = *temp;
}

FString USpiritBeast::GetName() const {
	return attribute.GetName();
}

FPassiveSkill USpiritBeast::GetPassiveSkill() const {
	return passiveSkill;
}

int32 USpiritBeast::GetFinallyHealth() const {
	return attribute.GetHealth() + WhichPassiveSkill(1);
}

int32 USpiritBeast::GetFinallyAttack() const {
	return attribute.GetAttack() + WhichPassiveSkill(2);
}

int32 USpiritBeast::GetFinallyDefense() const {
	return attribute.GetDefense() + WhichPassiveSkill(3);
}

int32 USpiritBeast::WhichPassiveSkill(int32 index) const {
	auto GetValue = [&](EPassiveSkill type) {
		return passiveSkill.GetPassiveSkill() == type ? passiveSkill.GetValue() : 0;
	};

	switch (index) {
		case 1:
			return GetValue(EPassiveSkill::Health);
			break;
		case 2:
			return GetValue(EPassiveSkill::Attack);
			break;
		case 3:
			return GetValue(EPassiveSkill::Defense);
			break;
		default:
			return 0;
			break;
	}
}
