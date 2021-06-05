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

FString FPassiveSkill::GetContent() const {
	return content;
}

USpiritBeast::USpiritBeast() {
	DecideContent();
}

void USpiritBeast::DecideContent() {
	const char* path = gSpiritBeast;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	int32 random = FMath::RandRange(0, rowNames.Num() - 1);
	FCommonAttribute* temp = pDataTable->FindRow<FCommonAttribute>(UDatasetBPLibrary::FromIntToFName(random), "");
	attribute = *temp;
}

FString USpiritBeast::GetName() {
	return attribute.GetName();
}
