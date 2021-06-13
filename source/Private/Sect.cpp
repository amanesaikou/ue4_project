// Fill out your copyright notice in the Description page of Project Settings.


#include "Sect.h"
#include "ComputeBPLibrary.h"
#include "Constant.h"

USect::USect() {
	SetFacility();
	spiritStone = 2000000000;
	medicinalMaterials = 10000000;
	bloodlinePill = 1000;
	for (int32 i = 0; i < 5; i++)
		AddEliteDisciple();
	for (int32 i = 0; i < 5; i++)
		AddEquipment();
	for (int32 i = 0; i < 5; i++)
		AddLaw();
}

void USect::EveryYear() {
	AddSpiritStone(facilities[0].GetValue());
	AddMedicinalMaterials(facilities[1].GetValue());
}

void USect::SetFacility() {
	const char* path = gFacility;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames = pDataTable->GetRowNames();
	for (int32 i = 0; i < rowNames.Num();i++) {
		FFacility* temp = pDataTable->FindRow<FFacility>(rowNames[i], "");
		facilities.Emplace(*temp);
	}
}

void USect::AddEliteDisciple() {
	FString objectName = "UEliteDisciple";
	objectName.AppendInt(eliteDiscipleNums++); 
	UEliteDisciple* temp = NewObject<UEliteDisciple>(this, FName(*objectName));
	eliteDisciples.Emplace(temp);
	FString str = Message::GetEmployDisciple(temp->GetRarityName(), temp->GetName());
	logs.Add(str);
}

void USect::EmployEliteDisciple() {
		AddEliteDisciple();
		UseSpiritStone(100);
}

bool USect::CanEmployDisciple() {
	return spiritStone > 100 && eliteDisciples.Num() < gDiscipleLimit ? true : false;
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
	if (CanAddEquipment(temp) == true) {
		AddRemoveEquipment(temp);
		FString str = Message::GetNewEquipment(temp->GetRarityName(), temp->GetName(), uint8(temp->GetType()));
		logs.Add(str);
	}
	else {
		AddSpiritStone(temp->GetPrice());
		FString str = Message::GetNewEquipment(temp->GetRarityName(), temp->GetName(), uint8(temp->GetType()), temp->GetPrice());
		logs.Add(str);
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
	if (CanAddLaw(temp) == true) {
		AddRemoveLaw(temp);
		FString str = Message::GetNewLaw(temp->GetRarityName(), temp->GetName(), uint8(temp->GetType()));
		logs.Add(str);
	}
	else {
		AddSpiritStone(temp->GetPrice());
		FString str = Message::GetNewLaw(temp->GetRarityName(), temp->GetName(), uint8(temp->GetType()), temp->GetPrice());
		logs.Add(str);
		temp = NULL;
	}
}

void USect::AddSpiritBeast() {
	FString objectName = "USpiritBeas";
	objectName.AppendInt(spiritBeastNums++);
	USpiritBeast* temp = NewObject<USpiritBeast>(this, FName(*objectName));
	spiritBeasts.Emplace(temp);
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

TArray<FFacility> USect::GetFacilities() {
	return facilities;
}

FFacility USect::GetFacility(int32 index) {
	return facilities[index];
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

TArray<USpiritBeast*> USect::GetSpiritBeasts() {
	return spiritBeasts;
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

void USect::SellSpiritBeast(int32 index) {
	AddSpiritStone(spiritBeasts[index]->GetPrice());
	spiritBeasts.RemoveAt(index);
}

bool USect::CanFacilityLevelUp(int index, int32 cost) {
	if (facilities[index].CanLevelUp() && spiritStone >= cost)
		return true;
	else
		return false;
}

void USect::FacilityLevelUp(int32 index, int32 cost, int32 value) {
	facilities[index].LevelUp();
	facilities[index].SetValue(value);
	FFacility temp = facilities[index];
	UseSpiritStone(cost);
	FString str = Message::GetFacilityLevelUp(temp.GetName(), temp.GetLevel(), cost);
	logs.Add(str);
}

void USect::UseSpiritStone(int32 cost) {
	spiritStone -= cost;
}

void USect::UseMedicinalMaterials(int32 cost) {
	medicinalMaterials -= cost;
}

void USect::UseBloodlinePills(int32 cost) {
	bloodlinePill -= cost;
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
	spiritStone = UComputeBPLibrary::CheckOverRange(spiritStone+num, gLimit);
}

int32 USect::GetSpiritStone() const {
	return spiritStone;
}

void USect::AddMedicinalMaterials(int32 num) {
	medicinalMaterials = UComputeBPLibrary::CheckOverRange(medicinalMaterials + num, gLimit);
}

int32 USect::GetMedicinalMaterials() const {
	return medicinalMaterials;
}

void USect::MakeBloodlinePills(int32 num) {
	medicinalMaterials -= num * facilities[2].GetValue();
	bloodlinePill += num;
}

int32 USect::GetBloodlinePills() const {
	return bloodlinePill;
}

TArray<FString> USect::GetLogs() const {
	return logs;
}

void USect::ClearLogs() {
	logs.Empty();
}
