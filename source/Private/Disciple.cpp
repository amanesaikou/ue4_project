// Fill out your copyright notice in the Description page of Project Settings.

#include "Disciple.h"
#include "Engine/World.h"
#include "MyGameInstance.h"
//#include <functional> // std::function
//#include "..\Public\Disciple.h"

UEliteDisciple::UEliteDisciple() {
	DecideRarity();
	DecideName();
	attriute.SetAttack(500 * (6 - uint8(rarity)));
	attriute.SetHealth(1000 * (6 - uint8(rarity)));
	attriute.SetDefense(300 * (6 - uint8(rarity)));
	DecideLifePalace();
	DecideStar();
}

void UEliteDisciple::DecideName() {
	attriute.SetName("aaa");
}

void UEliteDisciple::DecideRarity() {
	rarity = UTypeBPLibrary::DecideRarity<EDiscipleRarityType>(UPath::GetDiscipleRarityPath());
}

void UEliteDisciple::DecideLifePalace() {
	if (UTypeBPLibrary::IsSonofEra(rarity)) {
		int32 random = FMath::RandRange(1, 100);
		if (random < 96)
			lifePalace = 12;
		else
			lifePalace = 13;
	}

	else if (UTypeBPLibrary::IsGenius(rarity)) {
		int32 random = FMath::RandRange(1, 100);
		if (random < 81)
			lifePalace = 10;
		else
			lifePalace = 11;
	}

	else if (UTypeBPLibrary::IsExtraordinary(rarity)) {
		int32 random = FMath::RandRange(7, 9);
		lifePalace = random;
	}

	else if (UTypeBPLibrary::IsOutstanding(rarity)) {
		int32 random = FMath::RandRange(5, 6);
		lifePalace = random;
	}

	else if (UTypeBPLibrary::IsExcellent(rarity)) {
		int32 random = FMath::RandRange(2, 4);
		lifePalace = random;
	}

	else
		lifePalace = 1;
}

void UEliteDisciple::DecideStar() {
	if (!UTypeBPLibrary::IsNormal(rarity))
		stars = 9 - uint8(rarity) - FMath::RandRange(0, 1);

	else
		stars = FMath::RandRange(1, 3);

}

FString UEliteDisciple::GetName() const {
	return attriute.GetName();
}

EDiscipleRarityType UEliteDisciple::GetRarity() const {
	return rarity;
}

FString UEliteDisciple::GetRarityName() const {
	return UTypeBPLibrary::GetRarityName<EDiscipleRarityType>(UPath::GetDiscipleRarityPath(), rarity);
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
	}
}

void UEliteDisciple::WearWeapon(const TArray<UEquipment*>& weapons, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (weapon != NULL)
		MyGameInstance->GetSect()->AddEquipment(weapon);
	weapon = weapons[index];
	MyGameInstance->GetSect()->RemoveWeapon(index);
}


void UEliteDisciple::WearArtifact(const TArray<UEquipment*>& artifacts, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (artifact != NULL)
		MyGameInstance->GetSect()->AddEquipment(artifact);
	artifact = artifacts[index];
	MyGameInstance->GetSect()->RemoveArtifact(index);
}

void UEliteDisciple::WearHiddenWeapon(const TArray<UEquipment*>& hiddenWeapons, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (hiddenWeapon != NULL)
		MyGameInstance->GetSect()->AddEquipment(hiddenWeapon);
	hiddenWeapon = hiddenWeapons[index];
	MyGameInstance->GetSect()->RemoveHiddenWeapon(index);
}

void UEliteDisciple::UseLaw(const TArray<UCultivationLaw*>& laws, int32 index) {
	//cultivationLaw = laws[index];
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
	}
}

void UEliteDisciple::UseCultivationLaw(const TArray<UCultivationLaw*>& laws, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (cultivationLaw != NULL)
		MyGameInstance->GetSect()->AddLaw(cultivationLaw);
	cultivationLaw = laws[index];
	MyGameInstance->GetSect()->RemoveCultivationLaw(index);
	//Apply(laws, index, cultivationLaw);
}

void UEliteDisciple::UseWorkoutLaw(const TArray<UCultivationLaw*>& laws, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (workoutLaw != NULL)
		MyGameInstance->GetSect()->AddLaw(workoutLaw);
	workoutLaw = laws[index];
	MyGameInstance->GetSect()->RemoveWorkoutLaw(index);
	//Apply(laws, index, workoutLaw);
}

void UEliteDisciple::UseAttackSkill(const TArray<UCultivationLaw*>& laws, int32 index) {
	UMyGameInstance* MyGameInstance = GetGameInstance();
	if (attackSkill != NULL)
		MyGameInstance->GetSect()->AddLaw(attackSkill);
	attackSkill = laws[index];
	MyGameInstance->GetSect()->RemoveAttackSkill(index);
	//Apply(laws, index, attackSkill);
}

void UEliteDisciple::RemoveAll() {
	UMyGameInstance* MyGameInstance = GetGameInstance();

	auto RemoveEquipment = [&](UEquipment* equipment) {
		if (equipment != NULL)
			MyGameInstance->GetSect()->AddEquipment(equipment);
	};

	auto RemoveLaw = [&](UCultivationLaw* law) {
		if (law != NULL)
			MyGameInstance->GetSect()->AddLaw(law);
	};

	RemoveEquipment(weapon);
	RemoveEquipment(artifact);
	RemoveEquipment(hiddenWeapon);
	RemoveLaw(cultivationLaw);
	RemoveLaw(workoutLaw);
	RemoveLaw(attackSkill);
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
	const char* path = UPath::GetLifePalaceTitlePath();
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FCommonString* temp = pDataTable->FindRow<FCommonString>(UDatasetBPLibrary::FromIntToFName(lifePalace), "");
	FString title = temp->GetString();
	return title;
}

int32 UEliteDisciple::GetStar() const {
	return stars;
}

FString UEliteDisciple::GetStarTitle() const {
	const char* path = UPath::GetStarTitlePath();
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	FCommonString* temp = pDataTable->FindRow<FCommonString>(UDatasetBPLibrary::FromIntToFName(stars), "");
	FString title = temp->GetString();
	return title;
}
