// Fill out your copyright notice in the Description page of Project Settings.


#include "Sect.h"

USect::USect() {
	money = 1000000;
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
	if (temp->GetType() == EEquipmentType::Weapon) {
		if(weapons.Num() < 50)
			weapons.Emplace(temp);
	}
	else if (temp->GetType() == EEquipmentType::Artifact) {
		if (artifacts.Num() < 50)
			artifacts.Emplace(temp);
	}
	else {
		if (hiddenWeapons.Num() < 50)
			hiddenWeapons.Emplace(temp);
	}
}

void USect::AddEquipment(UEquipment* equipment) {
	if (equipment->GetType() == EEquipmentType::Weapon)
		weapons.Emplace(equipment);
	else if (equipment->GetType() == EEquipmentType::Artifact)
		artifacts.Emplace(equipment);
	else
		hiddenWeapons.Emplace(equipment);
}

void USect::AddLaw() {
	FString objectName = "UCultivationLaw";
	objectName.AppendInt(lawNums++);
	UCultivationLaw* temp = NewObject<UCultivationLaw>(this, FName(*objectName));
	if(temp->GetType() == ECultivationType::CultivationLaw)
		cultivationLaws.Emplace(temp);
	else if (temp->GetType() == ECultivationType::WorkoutLaw)
		workoutLaws.Emplace(temp);
	else
		attackSkills.Emplace(temp);
}

void USect::AddLaw(UCultivationLaw* law) {
	if (law->GetType() == ECultivationType::CultivationLaw)
		cultivationLaws.Emplace(law);
	else if (law->GetType() == ECultivationType::WorkoutLaw)
		workoutLaws.Emplace(law);
	else
		attackSkills.Emplace(law);
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

int32 USect::GetFinallyAttack() {
	int32 finallyAttack = 0;
	for (auto& i : eliteDisciples)
		finallyAttack += i->GetFinallyAttack();
	return finallyAttack;
}

int32 USect::GetFinallyHealth() {
	int32 finallyHealth = 0;
	for (auto& i : eliteDisciples)
		finallyHealth += i->GetFinallyHealth();
	return finallyHealth;
}

int32 USect::GetFinallyDefense() {
	int32 finallyDefense = 0;
	for (auto& i : eliteDisciples)
		finallyDefense += i->GetFinallyDefense();
	return finallyDefense;
}

void USect::DiscipleSort() {
	eliteDisciples.Sort([](const UEliteDisciple& A, const UEliteDisciple& B) {
		return A.rarity < B.rarity;
	});
}

void USect::CultivationLawSort(int32 index) {
	auto Sort = [](TArray<UCultivationLaw*>& laws) {
		laws.Sort([](const UCultivationLaw& A, const UCultivationLaw& B) {
			return A.rarity < B.rarity;
		});
		return;
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
		return;
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
