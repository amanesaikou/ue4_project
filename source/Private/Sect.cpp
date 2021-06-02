// Fill out your copyright notice in the Description page of Project Settings.


#include "Sect.h"
#include <thread> // std::thread

USect::USect() {
	spiritStone = 100000;
}

void USect::AddEliteDisciple() {
	FString objectName = "UEliteDisciple";
	objectName.AppendInt(eliteDiscipleNums++); 
	UEliteDisciple* temp = NewObject<UEliteDisciple>(this, FName(*objectName));
	eliteDisciples.Emplace(temp);
}

void USect::EmployEliteDisciple() {
		AddEliteDisciple();
		UseSpiritStone(100);
}

bool USect::CanEmployDisciple() {
	return spiritStone > 100 && eliteDisciples.Num() < 55 ? true : false;
}

void USect::ExpelDisciple(int32 index) {
	eliteDisciples[index]->RemoveAll();
	eliteDisciples.RemoveAt(index);
}

bool USect::CanExpelDisciple(int32 index) {

	auto CheckENumLimit = [&] (UEquipment* equipment,TArray<UEquipment*> equipments) {
		if (equipment != NULL && equipments.Num() == 50)
			return false;
		else
			return true;
	};

	auto CheckLNumLimit = [&](UCultivationLaw* law, TArray<UCultivationLaw*> laws) {
		if (law != NULL && laws.Num() == 50)
			return false;
		else
			return true;
	};

	if (!CheckENumLimit(eliteDisciples[index]->GetWeapon(), weapons))
		return false;

	else if (!CheckENumLimit(eliteDisciples[index]->GetArtifact(), artifacts))
		return false;

	else if (!CheckENumLimit(eliteDisciples[index]->GetHiddenWeapon(), hiddenWeapons))
		return false;

	else if (!CheckLNumLimit(eliteDisciples[index]->GetCultivationLaw(), cultivationLaws))
		return false;

	else if (!CheckLNumLimit(eliteDisciples[index]->GetWorkoutLaw(), workoutLaws))
		return false;

	else if (!CheckLNumLimit(eliteDisciples[index]->GetAttackSkill(), attackSkills))
		return false;

	else
		return true;

}

void USect::AddEquipment() {
	FString objectName = "UEquipment";
	objectName.AppendInt(equipmentNums++);
	UEquipment* temp = NewObject<UEquipment>(this, FName(*objectName));
	if (CanAddEquipment(temp) == true)
		AddRemoveEquipment(temp);
	else {
		AddSpiritStone(temp->GetPrice());
		temp = NULL;
	}
}

void USect::AddRemoveEquipment(UEquipment* equipment) {
	if (equipment->GetType() == EEquipmentType::Weapon)
		weapons.Emplace(equipment);
	else if (equipment->GetType() == EEquipmentType::Artifact)
		artifacts.Emplace(equipment);
	else
		hiddenWeapons.Emplace(equipment);
}

bool USect::CanAddEquipment(UEquipment* equipment) {
	auto GetReturn = [](TArray<UEquipment*> equipments) {
		return equipments.Num() < 50 ? true : false;
	};

	if (equipment->GetType() == EEquipmentType::Weapon)
		return GetReturn(weapons);

	else if (equipment->GetType() == EEquipmentType::Artifact)
		return GetReturn(artifacts);

	else
		return GetReturn(hiddenWeapons);
}

void USect::AddLaw() {
	FString objectName = "UCultivationLaw";
	objectName.AppendInt(lawNums++);
	UCultivationLaw* temp = NewObject<UCultivationLaw>(this, FName(*objectName));
	if (CanAddLaw(temp) == true)
		AddRemoveLaw(temp);
	else {
		AddSpiritStone(temp->GetPrice());
		temp = NULL;
	}
}

void USect::AddRemoveLaw(UCultivationLaw* law) {
	law->SetLevelZero();
	if (law->GetType() == ECultivationType::CultivationLaw)
		cultivationLaws.Emplace(law);
	else if (law->GetType() == ECultivationType::WorkoutLaw)
		workoutLaws.Emplace(law);
	else
		attackSkills.Emplace(law);
}

bool USect::CanAddLaw(UCultivationLaw* law) {
	auto GetReturn = [](TArray<UCultivationLaw*> laws) {
		return laws.Num() < 50 ? true : false;
	};

	if (law->GetType() == ECultivationType::CultivationLaw)
		return GetReturn(cultivationLaws);

	else if (law->GetType() == ECultivationType::WorkoutLaw)
		return GetReturn(workoutLaws);

	else
		return GetReturn(attackSkills);
}

TArray<UEliteDisciple*> USect::GetEliteDisciples() {
	return eliteDisciples;
}

TArray<UEquipment*> USect::GetWeapons() {
	return weapons;
}

TArray<UEquipment*> USect::GetArtifacts() {
	return artifacts;
}

TArray<UEquipment*> USect::GetHiddenWeapons() {
	return hiddenWeapons;
}

TArray<UCultivationLaw*> USect::GetCultivationLaws() {
	return cultivationLaws;
}

TArray<UCultivationLaw*> USect::GetWorkoutLaws() {
	return workoutLaws;
}

TArray<UCultivationLaw*> USect::GetAttackSkills() {
	return attackSkills;
}

void USect::RemoveEquipment(UEquipment* equipment, int32 index) {
	int32 type = uint8(equipment->GetType());
	switch (type) {
		case 0:
			RemoveWeapon(index);
			break;
		case 1:
			RemoveArtifact(index);
			break;
		case 2:
			RemoveHiddenWeapon(index);
			break;
		default:
			break;
	}
}

void USect::RemoveWeapon(int32 index) {
	weapons.RemoveAt(index);
}

void USect::RemoveArtifact(int32 index) {
	artifacts.RemoveAt(index);
}

void USect::RemoveHiddenWeapon(int32 index) {
	hiddenWeapons.RemoveAt(index);
}

void USect::RemoveCultivationLaw(int32 index) {
	cultivationLaws.RemoveAt(index);
}

void USect::RemoveWorkoutLaw(int32 index) {
	workoutLaws.RemoveAt(index);
}

void USect::RemoveAttackSkill(int32 index) {
	attackSkills.RemoveAt(index);
}

void USect::UseSpiritStone(int32 cost) {
	spiritStone -= cost;
}

void USect::AddAttribute(int32& attribute, std::function<int32(UEliteDisciple*)> Get){
	for (auto& i : eliteDisciples)
		attribute += Get(i);
}

int32 USect::GetFinallyAttack() {
	int32 finallyAttack = 0;
	AddAttribute(finallyAttack, &UEliteDisciple::GetFinallyAttack);
	return finallyAttack;
}

int32 USect::GetFinallyHealth() {
	int32 finallyHealth = 0;
	AddAttribute(finallyHealth, &UEliteDisciple::GetFinallyHealth);
	return finallyHealth;
}

int32 USect::GetFinallyDefense() {
	int32 finallyDefense = 0;
	AddAttribute(finallyDefense, &UEliteDisciple::GetFinallyDefense);
	return finallyDefense;
}

void USect::DiscipleSort() {
	eliteDisciples.Sort([](const UEliteDisciple& A, const UEliteDisciple& B) {
		/*
			弟子排序先比資質
			相同再比命宮數量
			相同再比星辰數量
		*/
		if (A.rarity == B.rarity) {
			if (A.GetLifePalace() == B.GetLifePalace())
				return A.GetStar() > B.GetStar();
			else
				return A.GetLifePalace() > B.GetLifePalace();
		}
		return A.rarity < B.rarity;
	});
}

void USect::CultivationLawSort(int32 index) {
	auto Sort = [](TArray<UCultivationLaw*>& laws) {
		// 功法排序比id
		laws.Sort([](const UCultivationLaw& A, const UCultivationLaw& B) {
			return A.GetID() < B.GetID();
		});
	};
	switch (index) {
		case 1:
			Sort(cultivationLaws);
			break;
		case 2:
			Sort(workoutLaws);
			break;
		case 3:
			Sort(attackSkills);
			break;
	}
}

void USect::EquipmentSort(int32 index) {
	auto Sort = [](TArray<UEquipment*>& equipments) {
		/*
			裝備排序先比id
			相同再比強化等級
			相同再比精煉等級
		*/
		equipments.Sort([](const UEquipment& A, const UEquipment& B) {
			if (A.GetID() == B.GetID()) {
				if (A.GetEnhancementLevel() == B.GetEnhancementLevel())
					return A.GetRefiningLevel() > B.GetRefiningLevel();
				else
					return A.GetEnhancementLevel() > B.GetEnhancementLevel();
			}
			else
				return A.GetID() < B.GetID();
		});
	};
	switch (index) {
	case 1:
		Sort(weapons);
		break;
	case 2:
		Sort(artifacts);
		break;
	case 3:
		Sort(hiddenWeapons);
		break;
	}
}

void USect::AddSpiritStone(int32 num) {
	spiritStone += num;
}

int32 USect::GetSpiritStone() const {
	return spiritStone;
}