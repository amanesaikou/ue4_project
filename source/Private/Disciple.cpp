// Fill out your copyright notice in the Description page of Project Settings.

#include "Disciple.h"
#include "Engine/World.h"
#include "MyGameInstance.h"
#include "Constant.h"
//#include <functional> // std::function
//#include "..\Public\Disciple.h"

UEliteDisciple::UEliteDisciple() {
	DecideRarity();
	DecideName();
	SetImageIndex();
	attriute.SetAttack(500 * (6 - uint8(rarity)));
	attriute.SetHealth(1000 * (6 - uint8(rarity)));
	attriute.SetDefense(300 * (6 - uint8(rarity)));
	DecideLifePalace();
	DecideStar();
}

void UEliteDisciple::Load(FDisciple dis, int32 i) {
	FString objectName = "LoadDisciple";
	objectName.AppendInt(i);
	objectName += "Equipmet";
	attriute = dis.attribute;

	auto LoadEquipment = [&] (int32 i, UEquipment* equip, FEquip& loadEquip) {
		objectName.AppendInt(i);
		UEquipment* temp = NewObject<UEquipment>(this, FName(*objectName));
		equip = temp;
		equip->Load(loadEquip);
		return equip;
	};

	if (dis.hasEquipments[0])
		weapon = LoadEquipment(1, weapon, dis.weapon);
	if (dis.hasEquipments[1])
		artifact = LoadEquipment(2, artifact, dis.artifact);
	if (dis.hasEquipments[2])
		hiddenWeapon = LoadEquipment(3, hiddenWeapon, dis.hiddenWeapon);

	rarity = dis.rarity;
	lifePalace = dis.lifePalace;
	stars = dis.stars;
	
}

FDisciple UEliteDisciple::Save() {
	auto EIsVaild = [&](UEquipment* equipment) {
		return equipment == NULL ? false : true;
	};
	FDisciple dis;
	dis.rarity = rarity;
	dis.attribute = attriute;
	if (EIsVaild(weapon)) {
		dis.weapon = weapon->Save();
		dis.hasEquipments[0] = true;
	}
	if (EIsVaild(artifact)) {
		dis.artifact = artifact->Save();
		dis.hasEquipments[1] = true;
	}
	if (EIsVaild(hiddenWeapon)) {
		dis.hiddenWeapon = hiddenWeapon->Save();
		dis.hasEquipments[2] = true;
	}
	dis.lifePalace = lifePalace;
	dis.stars = stars;

	return dis;
}

void UEliteDisciple::DecideName() {
	FString name = "";
	name += GetName(gSurname);
	name += GetName(gName);
	attriute.SetName(name);
}

FString UEliteDisciple::GetName(const char* path) const {
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	int32 row = FMath::RandRange(0, rowNames.Num() - 1);
	FCommonString* temp = pDataTable->FindRow<FCommonString>(UDatasetBPLibrary::FromIntToFName(row), "");
	FString name = temp->GetString();
	return name;
}

void UEliteDisciple::SetImageIndex() {
	int32 index = FMath::RandRange(0, 5);
	attriute.SetID(index);
}

int32 UEliteDisciple::GetImageIndex() const {
	return attriute.GetID();
}

void UEliteDisciple::DecideRarity() {
	rarity = UTypeBPLibrary::DecideRarity<EDiscipleRarityType>(gDiscipleRarity);
}

void UEliteDisciple::DecideLifePalace() {
	int32 random;
	// 根據資質決定命宮數量
	switch (rarity) {
	case EDiscipleRarityType::SonofEra:
		random = FMath::RandRange(1, 100);
		if (random < 96)
			lifePalace = 12;
		else
			lifePalace = 13;
		break;
	case EDiscipleRarityType::Genius:
		random = FMath::RandRange(1, 100);
		if (random < 81)
			lifePalace = 10;
		else
			lifePalace = 11;
		break;
	case EDiscipleRarityType::Extraordinary:
		random = FMath::RandRange(7, 9);
		lifePalace = random;
		break;
	case EDiscipleRarityType::Outstanding:
		random = FMath::RandRange(5, 6);
		lifePalace = random;
		break;
	case EDiscipleRarityType::Excellent:
		random = FMath::RandRange(2, 4);
		lifePalace = random;
		break;
	case EDiscipleRarityType::Normal:
		lifePalace = 1;
		break;
	default:
		break;
	}
}

void UEliteDisciple::DecideStar() {
	switch (rarity) {
	case EDiscipleRarityType::Normal:
		stars = 9 - uint8(rarity) - FMath::RandRange(0, 1);
		break;
	default:
		stars = FMath::RandRange(1, 3);
		break;
	}
}

FString UEliteDisciple::GetName() const {
	return attriute.GetName();
}

EDiscipleRarityType UEliteDisciple::GetRarity() const {
	return rarity;
}

FString UEliteDisciple::GetRarityName() const {
	return UTypeBPLibrary::GetRarityName<EDiscipleRarityType>(gDiscipleRarity, rarity);
}

int32 UEliteDisciple::GetFinallyAttack() const {

	int32 finallyAttack = 0;
	auto GetLawValue = [&](UCultivationLaw* law) {
		if (law != NULL)
			return law->GetFinallyAttack();
		else
			return 0;
	};

	auto GetEquipmentValue = [&](UEquipment* equipment) {
		if (equipment != NULL)
			return equipment->GetFinallyAttack();
		else
			return 0;
	};

	finallyAttack += GetLawValue(cultivationLaw);
	finallyAttack += GetLawValue(workoutLaw);
	finallyAttack += GetLawValue(attackSkill);
	finallyAttack += GetEquipmentValue(weapon);
	finallyAttack += GetEquipmentValue(artifact);
	finallyAttack += GetEquipmentValue(hiddenWeapon);

	return attriute.GetAttack() * GetBuff() + finallyAttack;
}

int32 UEliteDisciple::GetFinallyHealth() const {

	int32 finallyHealth = 0;
	auto GetLawValue = [&](UCultivationLaw* law) {
		if (law != NULL)
			return law->GetFinallyHealth();
		else
			return 0;
	};

	auto GetEquipmentValue = [&](UEquipment* equipment) {
		if (equipment != NULL)
			return equipment->GetFinallyHealth();
		else
			return 0;
	};

	finallyHealth += GetLawValue(cultivationLaw);
	finallyHealth += GetLawValue(workoutLaw);
	finallyHealth += GetLawValue(attackSkill);
	finallyHealth += GetEquipmentValue(weapon);
	finallyHealth += GetEquipmentValue(artifact);
	finallyHealth += GetEquipmentValue(hiddenWeapon);

	return attriute.GetHealth() * GetBuff() + finallyHealth;
}

int32 UEliteDisciple::GetFinallyDefense() const {
	
	int32 finallyDefense = 0;
	auto GetLawValue = [&](UCultivationLaw* law) {
		if (law != NULL)
			return law->GetFinallyDefense();
		else
			return 0;
	};

	auto GetEquipmentValue = [&](UEquipment* equipment) {
		if (equipment != NULL)
			return equipment->GetFinallyDefense();
		else
			return 0;
	};

	finallyDefense += GetLawValue(cultivationLaw);
	finallyDefense += GetLawValue(workoutLaw);
	finallyDefense += GetLawValue(attackSkill);
	finallyDefense += GetEquipmentValue(weapon);
	finallyDefense += GetEquipmentValue(artifact);
	finallyDefense += GetEquipmentValue(hiddenWeapon);

	return attriute.GetDefense() * GetBuff() + finallyDefense;
}

float UEliteDisciple::GetBuff() const {
	return 1.0 + lifePalace + float(stars * 0.5);
}

void UEliteDisciple::WearEquipment(const TArray<UEquipment*>& equipments, int32 index) {
	switch (equipments[index]->GetType()) {
	case EEquipmentType::Weapon:
		WearWeapon(equipments, index);
		break;
	case EEquipmentType::Artifact :
		WearArtifact(equipments, index);
		break;
	case EEquipmentType::HiddenWeapon :
		WearHiddenWeapon(equipments, index);
		break;
	default:
		break;
	}
	UMyGameInstance* MyGameInstance = GetGameInstance();
	MyGameInstance->GetSect()->RemoveEquipment(equipments[index], index);
}

void UEliteDisciple::WearWeapon(const TArray<UEquipment*>& weapons, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (weapon != NULL)
		MyGameInstance->GetSect()->AddRemoveEquipment(weapon);
	weapon = weapons[index];
}


void UEliteDisciple::WearArtifact(const TArray<UEquipment*>& artifacts, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (artifact != NULL)
		MyGameInstance->GetSect()->AddRemoveEquipment(artifact);
	artifact = artifacts[index];
}

void UEliteDisciple::WearHiddenWeapon(const TArray<UEquipment*>& hiddenWeapons, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (hiddenWeapon != NULL)
		MyGameInstance->GetSect()->AddRemoveEquipment(hiddenWeapon);
	hiddenWeapon = hiddenWeapons[index];
}

void UEliteDisciple::UseLaw(const TArray<UCultivationLaw*>& laws, int32 index) {
	switch (laws[index]->GetType()) {
	case ECultivationType::CultivationLaw :
		UseCultivationLaw(laws, index);
		break;
	case ECultivationType::WorkoutLaw :
		UseWorkoutLaw(laws, index);
		break;
	case ECultivationType::AttackSkill :
		UseAttackSkill(laws, index);
		break;
	default:
		break;
	}
	UMyGameInstance* MyGameInstance = GetGameInstance();
	MyGameInstance->GetSect()->RemoveLaw(laws[index], index);
}

void UEliteDisciple::UseCultivationLaw(const TArray<UCultivationLaw*>& laws, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (cultivationLaw != NULL)
		MyGameInstance->GetSect()->AddRemoveLaw(cultivationLaw);
	cultivationLaw = laws[index];
}

void UEliteDisciple::UseWorkoutLaw(const TArray<UCultivationLaw*>& laws, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (workoutLaw != NULL)
		MyGameInstance->GetSect()->AddRemoveLaw(workoutLaw);
	workoutLaw = laws[index];
}

void UEliteDisciple::UseAttackSkill(const TArray<UCultivationLaw*>& laws, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (attackSkill != NULL)
		MyGameInstance->GetSect()->AddRemoveLaw(attackSkill);
	attackSkill = laws[index];
}

void UEliteDisciple::RemoveAll() {
	UMyGameInstance* MyGameInstance = GetGameInstance();

	auto RemoveEquipment = [&](UEquipment* equipment) {
		if (equipment != NULL)
			MyGameInstance->GetSect()->AddRemoveEquipment(equipment);
	};

	auto RemoveLaw = [&](UCultivationLaw* law) {
		if (law != NULL)
			MyGameInstance->GetSect()->AddRemoveLaw(law);
	};

	RemoveEquipment(weapon);
	RemoveEquipment(artifact);
	RemoveEquipment(hiddenWeapon);
	RemoveLaw(cultivationLaw);
	RemoveLaw(workoutLaw);
	RemoveLaw(attackSkill);
}

void UEliteDisciple::RemoveEquipment(UEquipment* equipment) {
	if (equipment->GetType() == EEquipmentType::Weapon)
		weapon = NULL;
	else if (equipment->GetType() == EEquipmentType::Artifact)
		artifact = NULL;
	else
		hiddenWeapon = NULL;
}

void UEliteDisciple::RemoveLaw(UCultivationLaw* law) {
	if (law->GetType() == ECultivationType::CultivationLaw)
		cultivationLaw = NULL;
	else if (law->GetType() == ECultivationType::WorkoutLaw)
		workoutLaw = NULL;
	else
		attackSkill = NULL;
}

UMyGameInstance* UEliteDisciple::GetGameInstance() const {
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	return MyGameInstance;
}

UEquipment* UEliteDisciple::GetWeapon() const {
	return weapon;
}

UEquipment* UEliteDisciple::GetArtifact() const {
	return artifact;
}

UEquipment* UEliteDisciple::GetHiddenWeapon() const {
	return hiddenWeapon;
}

UCultivationLaw* UEliteDisciple::GetCultivationLaw() const {
	return cultivationLaw;
}

UCultivationLaw* UEliteDisciple::GetWorkoutLaw() const {
	return workoutLaw;
}

UCultivationLaw* UEliteDisciple::GetAttackSkill() const {
	return attackSkill;
}
int32 UEliteDisciple::GetLifePalace() const {
	return lifePalace;
}

FString UEliteDisciple::GetLifePalaceTitle() const {
	const char* path = gLifePalaceTitle;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FCommonString* temp = pDataTable->FindRow<FCommonString>(UDatasetBPLibrary::FromIntToFName(lifePalace), "");
	FString title = temp->GetString();
	return title;
}

int32 UEliteDisciple::GetStar() const {
	return stars;
}

FString UEliteDisciple::GetStarTitle() const {
	const char* path = gStarTitle;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FCommonString* temp = pDataTable->FindRow<FCommonString>(UDatasetBPLibrary::FromIntToFName(stars), "");
	FString title = temp->GetString();
	return title;
}
