// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleEquipment.h"

void UHandleEquipment::AddEquipment(USect* sect) {
	FEquipment temp;
	temp.Create();
	switch (temp.type)
	{
	case EEquipmentType::Weapon:
		sect->weapons.Emplace(temp);
		break;
	case EEquipmentType::Artifact:
		sect->artifacts.Emplace(temp);
		break;
	case EEquipmentType::HiddenWeapon:
		sect->hiddenWeapons.Emplace(temp);
		break;
	default:
		break;
	}
}

void UHandleEquipment::AddSingleEquipment(USect* sect, FEquipment equipment) {
	switch (equipment.type)
	{
	case EEquipmentType::Weapon:
		sect->weapons.Emplace(equipment);
		break;
	case EEquipmentType::Artifact:
		sect->artifacts.Emplace(equipment);
		break;
	case EEquipmentType::HiddenWeapon:
		sect->hiddenWeapons.Emplace(equipment);
		break;
	default:
		break;
	}
}

bool UHandleEquipment::CanAddEquipment(USect* sect, EEquipmentType type) {
	int32 num = GetSingleEquipmentNum(sect, type);
	// 單種裝備最多150件
	return num <= 150 ? true : false;
}

void UHandleEquipment::Sort(USect* sect, int32 mode) {
	auto ESort = [](TArray<FEquipment>& equip)  {
		equip.StableSort([](const FEquipment& A, const FEquipment& B) {
			return A.attribute.id < B.attribute.id;
		});
	};
	switch (mode)
	{
	case 1:
		ESort(sect->weapons);
		break;
	case 2:
		ESort(sect->artifacts);
		break;
	case 3:
		ESort(sect->hiddenWeapons);
		break;
	default:
		break;
	}
}

bool UHandleEquipment::HasEquipment(FEquipment e) {
	if (e.attribute.id == 0)
		return false;
	else
		return true;
}

void UHandleEquipment::SellEquipment(USect* sect, int32 index, EEquipmentType type) {
	switch (type)
	{
	case EEquipmentType::Weapon:
		sect->spiritStone += sect->weapons[index].price;
		sect->weapons.RemoveAt(index);
		break;
	case EEquipmentType::Artifact:
		sect->spiritStone += sect->artifacts[index].price;
		sect->artifacts.RemoveAt(index);
		break;
	case EEquipmentType::HiddenWeapon:
		sect->spiritStone += sect->hiddenWeapons[index].price;
		sect->hiddenWeapons.RemoveAt(index);
		break;
	default:
		break;
	}
}

FText UHandleEquipment::GetName(FEquipment e) {
	return e.attribute.name;
}

int32 UHandleEquipment::GetHealth(FEquipment e) {
	return FMath::RoundToInt(float(e.attribute.health) * (1.0 + e.enhanceLevel * 0.05));
}

int32 UHandleEquipment::GetDamage(FEquipment e) {
	return FMath::RoundToInt(float(e.attribute.attack) * (1.0 + e.enhanceLevel * 0.05));
}

int32 UHandleEquipment::GetDefense(FEquipment e) {
	return FMath::RoundToInt(float(e.attribute.defense) * (1.0 + e.enhanceLevel * 0.05));
}

bool UHandleEquipment::CanEnhance(USect* sect, FEquipment e) {
	TArray<int32> costs = { 1200, 700, 450, 350, 200, 150 , 100 };
	if (sect->spiritStone >= costs[uint8(e.rarity)] && e.IsMaxLevel())
		return true;
	else
		return false;
}

bool UHandleEquipment::Enhance(USect* sect, int32 index, int32 which, EEquipmentType type) {
	// 在弟子身上
	if (which == 1) {
		switch (type)
		{
		case EEquipmentType::Weapon:
			return sect->disciples[index].weapon.LevelUp(sect->spiritStone);
			break;
		case EEquipmentType::Artifact:
			return sect->disciples[index].artifact.LevelUp(sect->spiritStone);
			break;
		case EEquipmentType::HiddenWeapon:
			return sect->disciples[index].hiddenWeapon.LevelUp(sect->spiritStone);
			break;
		default:
			return false;
			break;
		}
	}
	else {
		switch (type)
		{
		case EEquipmentType::Weapon:
			return sect->weapons[index].LevelUp(sect->spiritStone);
			break;
		case EEquipmentType::Artifact:
			return sect->artifacts[index].LevelUp(sect->spiritStone);
			break;
		case EEquipmentType::HiddenWeapon:
			return sect->hiddenWeapons[index].LevelUp(sect->spiritStone);
			break;
		default:
			return false;
			break;
		}
	}
}

int32 UHandleEquipment::GetSingleEquipmentNum(USect* sect, EEquipmentType type) {
	int32 num = 0;

	switch (type)
	{
	case EEquipmentType::Weapon:
		for (auto& i : sect->disciples) {
			if (HasEquipment(i.weapon))
				++num;
		}
		num += sect->weapons.Num();
		break;
	case EEquipmentType::Artifact:
		for (auto& i : sect->disciples) {
			if (HasEquipment(i.artifact))
				++num;
		}
		num += sect->artifacts.Num();
		break;
	case EEquipmentType::HiddenWeapon:
		for (auto& i : sect->disciples) {
			if (HasEquipment(i.hiddenWeapon))
				++num;
		}
		num += sect->hiddenWeapons.Num();
		break;
	default:
		break;
	}

	return num;
}

