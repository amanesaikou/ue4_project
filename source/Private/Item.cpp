// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Constant.h"

FCommonAttribute::FCommonAttribute() {
	id = 0;
	name = "";
	attack = 0;
	health = 0;
	defense = 0;
}

int32 FCommonAttribute::GetID() const {
	return id;
}

FString FCommonAttribute::GetName() const {
	return name;
}

int32 FCommonAttribute::GetAttack() const {
	return attack;
}

int32 FCommonAttribute::GetHealth() const {
	return health;
}

int32 FCommonAttribute::GetDefense() const {
	return defense;
}

void FCommonAttribute::SetID(int32 tempID) {
	id = tempID;
}

void FCommonAttribute::SetName(FString tempName) {
	name = tempName;
}

void FCommonAttribute::SetAttack(int32 tempAttack) {
	attack = tempAttack;
}

void FCommonAttribute::SetHealth(int32 tempHealth) {
	health = tempHealth;
}

void FCommonAttribute::SetDefense(int32 tempDefense) {
	defense = tempDefense;
}

UItem::UItem() {
	DecideRarity();
	TArray<int32> prices = { 10000, 4000, 1000, 300, 100, 50, 20 };
	int32 r = uint8(rarity);
	int32 min = prices[r] - prices[r] * 0.2;
	int32 max = prices[r] + prices[r] * 0.2;
	price = FMath::RandRange(min, max);
}

int32 UItem::GetID() const {
	return attribute.GetID();
}

void UItem::DecideRarity() {
	rarity = UTypeBPLibrary::DecideRarity<EItemRarityType>(gItemRarity);
}

uint8 UItem::GetRarity() const {
	return uint8(rarity);
}

FString UItem::GetName() const {
	return attribute.GetName();
}

FString UItem::GetRarityName() const {
	return UTypeBPLibrary::GetRarityName(gItemRarity, rarity);
}

int32 UItem::GetPrice() const {
	return price;
}

UEquipment::UEquipment() {
	DecideType();
	DecideContent();
	enhancementLevel = 0;
	refiningLevel = 0;
}

void UEquipment::Load(FEquip equipment) {
	rarity = equipment.rarity;
	attribute = equipment.attribute;
	price = equipment.price;
	equipmentType = equipment.equipmentType;
	enhancementLevel = equipment.enhancementLevel;
	refiningLevel = equipment.refiningLevel;
}


FEquip UEquipment::Save() {
	FEquip equipment;
	equipment.rarity = rarity;
	equipment.attribute = attribute;
	equipment.price = price;
	equipment.equipmentType = equipmentType;
	equipment.enhancementLevel = enhancementLevel;
	equipment.refiningLevel = refiningLevel;
	return equipment;
}

void UEquipment::DecideType() {
	equipmentType = UTypeBPLibrary::DecideType<EEquipmentType>();
}

EEquipmentType UEquipment::GetType() const {
	return equipmentType;
}

void UEquipment::DecideContent() {
	// 3種裝備 7種階級
	int32 index = int32(uint8(rarity) + uint8(equipmentType) * 7);
	const char* path = UDatasetBPLibrary::GetTablePath(gEquipmentTablePath, index);
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	int32 random = FMath::RandRange(0, rowNames.Num() - 1);
	FCommonAttribute* temp = pDataTable->FindRow<FCommonAttribute>(UDatasetBPLibrary::FromIntToFName(random), "");
	attribute = *temp;
}

void UEquipment::Enhance() {
		enhancementLevel += 1;
}

bool UEquipment::CanEnhance(int32 spiritStone) {
	if (spiritStone >= GetEnhancementCost() && enhancementLevel < gEnhanceLimit)
		return true;
	else
		return false;
}

int32 UEquipment::GetEnhancementCost() const {
	// 每等強化費用為50靈石*等級
	return 50 * (enhancementLevel + 1);
}

void UEquipment::Refine() {
	refiningLevel += 1;
}

bool UEquipment::CanRefine(int32 spiritStone) {
	if (spiritStone >= GetRefiningCost() && refiningLevel < gRefineLimit)
		return true;
	else
		return false;
}

int32 UEquipment::GetRefiningCost() const {
	// 每等精煉費用為100靈石*等級
	return 100 * (refiningLevel + 1);
}

int32 UEquipment::GetEnhancementLevel() const {
	return enhancementLevel;
}

int32 UEquipment::GetRefiningLevel() const {
	return refiningLevel;
}

int32 UEquipment::GetFinallyAttack() const {
	return attribute.GetAttack() * GetBuff();
}

int32 UEquipment::GetFinallyHealth() const {
	return attribute.GetHealth() * GetBuff();
}

int32 UEquipment::GetFinallyDefense() const {
	return attribute.GetDefense() * GetBuff();
}

float UEquipment::GetBuff() const {
	// 強化等級每級+10% 精煉等級每級+25%
	return 1.0 + float(enhancementLevel * 0.1) + float(refiningLevel * 0.25);
}

UCultivationLaw::UCultivationLaw() {
	DecideType();
	DecideLaw();
	lawLevel = 1;
}

void UCultivationLaw::Load(FLaw law) {
	rarity = law.rarity;
	attribute = law.attribute;
	price = law.price;
	cultivationType = law.cultivationType;
	lawLevel = law.lawLevel;
}

FLaw UCultivationLaw::Save() {
	FLaw law;
	law.rarity = rarity;
	law.attribute = attribute;
	law.price = price;
	law.cultivationType = cultivationType;
	law.lawLevel = lawLevel;
	return law;
}

void UCultivationLaw::DecideType() {
	cultivationType = UTypeBPLibrary::DecideType<ECultivationType>();
}

void UCultivationLaw::DecideLaw() {
	// 3種功法 7種階級
	int32 index = int32(uint8(rarity) + uint8(cultivationType) * 7);
	const char* path = UDatasetBPLibrary::GetTablePath(gLawTablePath, index);
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	int32 random = FMath::RandRange(0, rowNames.Num() - 1);
	FCommonAttribute* temp = pDataTable->FindRow<FCommonAttribute>(UDatasetBPLibrary::FromIntToFName(random), "");
	attribute = *temp;
}

void UCultivationLaw::LevelUp(){
	lawLevel += 1;
}

bool UCultivationLaw::CanLevelUp(int32 spiritStone) {
	if (spiritStone >= GetLevelUpCost() && lawLevel < gLawLevelLimit)
		return true;
	else
		return false;
}

int32 UCultivationLaw::GetLevel() const {
	return lawLevel;
}

void UCultivationLaw::SetLevelZero() {
	lawLevel = 1;
}

FString UCultivationLaw::GetLevelName() const {
	const char* path = gLawLevel;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FCommonData* data = pDataTable->FindRow<FCommonData>(UDatasetBPLibrary::FromIntToFName(lawLevel), "");
	FString name = data->GetName();
	return name;
}

int32 UCultivationLaw::GetLevelUpCost() const {
	const char* path = gLawLevel;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FCommonData* data = pDataTable->FindRow<FCommonData>(UDatasetBPLibrary::FromIntToFName(lawLevel), "");
	int32 cost = data->GetNumber(); 
	return cost;
}

ECultivationType UCultivationLaw::GetType() const {
	return cultivationType;
}

int32 UCultivationLaw::GetFinallyAttack() const {
	return attribute.GetAttack() * (1 + lawLevel * 0.5);
}

int32 UCultivationLaw::GetFinallyHealth() const {
	return attribute.GetHealth() * (1 + lawLevel * 0.5);
}

int32 UCultivationLaw::GetFinallyDefense() const {
	return attribute.GetDefense() * (1 + lawLevel * 0.5);
}