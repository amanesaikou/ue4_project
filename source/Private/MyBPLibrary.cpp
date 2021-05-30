// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBPLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/UObjectGlobals.h"

FCommonData::FCommonData() {
	name = "";
	number = 0;
}

FString FCommonData::GetName() const {
	return name;
}

int32 FCommonData::GetNumber() const {
	return number;
}

FDataTablePath::FDataTablePath() {
	tablePath = "";
}

const char* FDataTablePath::GetPath() const{
	return TCHAR_TO_ANSI(*tablePath);
}

FCommonString::FCommonString() {
	str = "";
}

FString FCommonString::GetString() const {
	return str;
}

template<class T>
T UTypeBPLibrary::DecideRarity(const char* tablePath) {
	//const char* tablePath = UPath::GetDiscipleRarityPath();
	TArray<int32> rarityProbabilities = UDatasetBPLibrary::GetRarityProbability(tablePath);
	uint8 index;
	index = GetRarityIndex(rarityProbabilities);
	return T(index);
}

uint8 UTypeBPLibrary::GetRarityIndex(TArray<int32>& probabilities) {
	int32 random = FMath::RandRange(1, 100);
	uint8 index;
	for (index = 0; index < probabilities.Num(); index++)
		if (random <= probabilities[index])
			break;
	return uint8(index);
}

FLinearColor UTypeBPLibrary::GetDiscipleColor(EDiscipleRarityType rarity) {
	// ¶À ¬õ µµ ÂÅ ºñ ¶Â
	TArray<uint8> R = { 255, 255, 153, 0, 0, 0 };
	TArray<uint8> G = { 255, 0, 0, 0, 255, 0 };
	TArray<uint8> B = { 0, 0, 255, 235, 0, 0 };
	int32 index = int32(uint8(rarity));
	return FLinearColor(FColor(R[index], G[index], B[index]));
}

bool UTypeBPLibrary::IsSonofEra(EDiscipleRarityType rarity) {
	return rarity == EDiscipleRarityType::SonofEra ? true : false;
}

bool UTypeBPLibrary::IsGenius(EDiscipleRarityType rarity) {
	return rarity == EDiscipleRarityType::Genius ? true : false;
}

bool UTypeBPLibrary::IsExtraordinary(EDiscipleRarityType rarity) {
	return rarity == EDiscipleRarityType::Extraordinary ? true : false;
}

bool UTypeBPLibrary::IsOutstanding(EDiscipleRarityType rarity) {
	return rarity == EDiscipleRarityType::Outstanding ? true : false;
}

bool UTypeBPLibrary::IsExcellent(EDiscipleRarityType rarity) {
	return rarity == EDiscipleRarityType::Excellent ? true : false;
}

bool UTypeBPLibrary::IsNormal(EDiscipleRarityType rarity) {
	return rarity == EDiscipleRarityType::Normal ? true : false;
}

template<class T>
T UTypeBPLibrary::DecideType() {
	int32 random = FMath::RandRange(0, 2);
	return T(uint8(random));
}

template<class T>
FString UTypeBPLibrary::GetRarityName(const char* tablePath, T rarity) {
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(tablePath));
	FName rowName = UDatasetBPLibrary::FromIntToFName(int32(rarity));
	FCommonData* row = pDataTable->FindRow<FCommonData>(rowName, "");
	FString temp = row->GetName();
	return temp;
}

TArray<int32> UDatasetBPLibrary::GetRarityProbability(const char* tablePath) {
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(tablePath));
	TArray<FName> rowNames = pDataTable->GetRowNames();

	TArray<int32> rarityProbabilities;

	for (auto& row : rowNames) {
		FCommonData* temp = pDataTable->FindRow<FCommonData>(row, "");
		rarityProbabilities.Add(temp->GetNumber());
	}

	return rarityProbabilities;
}

const char* UDatasetBPLibrary::GetTablePath(const char* path, int32 index) {
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FDataTablePath* temp = pDataTable->FindRow<FDataTablePath>(FromIntToFName(index), "");
	const char* p = temp->GetPath();
	return p;
}

FName UDatasetBPLibrary::FromIntToFName(int32 num) {
	return FName(*FString::FromInt(num));
}

const char* UPath::GetLawLevelPath() {
	return "DataTable'/Game/StarterContent/Datatable/LawLevel/LawLevel.LawLevel'";
}

const char* UPath::GetItemRarityPath() {
	return "DataTable'/Game/StarterContent/Datatable/Rarity/ItemRarity.ItemRarity'";
}

const char* UPath::GetDiscipleRarityPath() {
	return "DataTable'/Game/StarterContent/Datatable/Rarity/DiscipleRarity.DiscipleRarity'";
}

const char* UPath::GetLawTablePath() {
	return "DataTable'/Game/StarterContent/Datatable/ItemTablePath/LawTablePath.LawTablePath'";
}

const char* UPath::GetEquipmentTablePath() {
	return "DataTable'/Game/StarterContent/Datatable/ItemTablePath/EquipmentTablePath.EquipmentTablePath'";
}

const char* UPath::GetLifePalaceTitlePath() {
	return "DataTable'/Game/StarterContent/Datatable/Title/LifePalaceTitle.LifePalaceTitle'";
}

const char* UPath::GetStarTitlePath() {
	return "DataTable'/Game/StarterContent/Datatable/Title/StarTitle.StarTitle'";
}
