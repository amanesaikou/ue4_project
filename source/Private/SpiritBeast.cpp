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
	DecideClass();
	price = FMath::RandRange(10000, 30000);
	bloodLineValue = 0;
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

void USpiritBeast::DecideClass() {
	DecideStar();
	DecideGrade();
	blood = 1;
}

void USpiritBeast::DecideStar() {
	// 40 30 18 9 3
	int32 random = FMath::RandRange(1, 100);
	if (random < 41)
		star = 1;
	else if (random < 71)
		star = 2;
	else if (random < 89)
		star = 3;
	else if (random < 98)
		star = 4;
	else
		star = 5;
}

void USpiritBeast::DecideGrade() {
	// 50 35 12 3 
	int32 random = FMath::RandRange(1, 100);
	if (random < 51)
		grade = 1;
	else if (random < 86)
		grade = 2;
	else if (random < 98)
		grade = 3;
	else
		grade = 4;
}

FString USpiritBeast::GetName() const {
	return attribute.GetName();
}

int32 USpiritBeast::GetStar() const {
	return star;
}

int32 USpiritBeast::GetBlood() const {
	return blood;
}

int32 USpiritBeast::GetGrade() const {
	return grade;
}

FPassiveSkill USpiritBeast::GetPassiveSkill() const {
	return passiveSkill;
}

int32 USpiritBeast::GetFinallyHealth() const {
	return attribute.GetHealth() * GetBuff() + WhichPassiveSkill(1);
}

int32 USpiritBeast::GetFinallyAttack() const {
	return attribute.GetAttack() * GetBuff() + WhichPassiveSkill(2);
}

int32 USpiritBeast::GetFinallyDefense() const {
	return attribute.GetDefense() * GetBuff() + WhichPassiveSkill(3);
}

float USpiritBeast::GetBuff() const {
	return 1.0 + float(star) * 0.2 + float(blood) * 0.25 + float(grade) * 0.3;
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

int32 USpiritBeast::GetPrice() const {
	return price;
}

int32 USpiritBeast::UsePill(int32 value) {
	int32 i = 1;
	for (i; i < value; i++) {
		bloodLineValue += FMath::RandRange(5, 10);
		if (bloodLineValue >= gBloodLine[blood-1]) {
			bloodLineValue -= gBloodLine[blood-1];
			blood += 1;
		}
		if (blood == 4) {
			return i;
		}
	}
	return i;
}

int32 USpiritBeast::GetBloodLineValue() const {
	return bloodLineValue;
}

int32 USpiritBeast::GetNextBloodValue() const {
	return gBloodLine[blood-1];
}
