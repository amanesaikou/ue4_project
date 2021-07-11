// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleDisciple.h"
#include "HandleEquipment.h"
#include "HandleLaw.h"
#include "Constant.h"

FString Read(int32 index) {
	const char* path = "DataTable'/Game/DataTable/Message/DisMessage.DisMessage'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FReadStr* data = pDataTable->FindRow<FReadStr>(FName(*FString::FromInt(index)), "");
		if (data != NULL) {
			return data->str;
		}
	}
	return FString();
}

void UHandleDisciple::AddDisciple(USect* sect) {
	FDisciple temp;
	sect->disciples.Emplace(temp);
}

void UHandleDisciple::Sort(USect* sect) {
	sect->disciples.StableSort([](const FDisciple& A, const FDisciple& B) {
		/*
			弟子排序先比資質
			相同再比命宮數量
			相同再比星辰數量
		*/
		/**
		if (A.rarity == B.rarity) {
			if (A.lifePalace == B.lifePalace)
				return A.star > B.star;
			else
				return A.lifePalace > B.lifePalace;
		}
		*/
		if (A.rarity == B.rarity) {
			if (A.lifePalace == B.lifePalace) {
				if (A.star == B.star) {
					if (A.personality == B.personality)
						return A.background < B.background;
					else
						return A.personality < B.personality;
				}
				else return A.star > B.star;
			}
			else
				return A.lifePalace > B.lifePalace;
		}
		return A.rarity < B.rarity;
	});
}

void UHandleDisciple::Expel(USect* sect, int32 index) {
	sect->disciples.RemoveAt(index);
}

void UHandleDisciple::UseEquipment(USect* sect, int32 disIndex, int32 equipIndex, EEquipmentType type) {
	switch (type)
	{
	case EEquipmentType::Weapon:
		if(UHandleEquipment::HasEquipment(sect->disciples[disIndex].weapon)) 
			sect->weapons.Emplace(sect->disciples[disIndex].weapon);
		sect->disciples[disIndex].weapon = sect->weapons[equipIndex];
		sect->weapons.RemoveAt(equipIndex);
		break;
	case EEquipmentType::Artifact:
		if (UHandleEquipment::HasEquipment(sect->disciples[disIndex].artifact))
			sect->artifacts.Emplace(sect->disciples[disIndex].artifact);
		sect->disciples[disIndex].artifact = sect->artifacts[equipIndex];
		sect->artifacts.RemoveAt(equipIndex);
		break;
	case EEquipmentType::HiddenWeapon:
		if (UHandleEquipment::HasEquipment(sect->disciples[disIndex].hiddenWeapon))
			sect->hiddenWeapons.Emplace(sect->disciples[disIndex].hiddenWeapon);
		sect->disciples[disIndex].hiddenWeapon = sect->hiddenWeapons[equipIndex];
		sect->hiddenWeapons.RemoveAt(equipIndex);
		break;
	default:
		break;
	}
}

void UHandleDisciple::SellEquipment(USect* sect, int32 index, EEquipmentType type) {
	FEquipment temp;
	switch (type)
	{
	case EEquipmentType::Weapon:
		sect->spiritStone += sect->disciples[index].weapon.price;
		sect->disciples[index].weapon = temp;
		break;
	case EEquipmentType::Artifact:
		sect->spiritStone += sect->disciples[index].artifact.price;
		sect->disciples[index].artifact = temp;
		break;
	case EEquipmentType::HiddenWeapon:
		sect->spiritStone += sect->disciples[index].hiddenWeapon.price;
		sect->disciples[index].hiddenWeapon = temp;
		break;
	default:
		break;
	} 
}

void UHandleDisciple::RemoveEquipment(USect* sect, int32 disIndex, EEquipmentType type) {
	FEquipment temp;
	switch (type)
	{
	case EEquipmentType::Weapon:
		sect->weapons.Emplace(sect->disciples[disIndex].weapon);
		sect->disciples[disIndex].weapon = temp;
		break;
	case EEquipmentType::Artifact:
		sect->artifacts.Emplace(sect->disciples[disIndex].artifact);
		sect->disciples[disIndex].artifact = temp;
		break;
	case EEquipmentType::HiddenWeapon:
		sect->hiddenWeapons.Emplace(sect->disciples[disIndex].hiddenWeapon);
		sect->disciples[disIndex].hiddenWeapon = temp;
		break;
	default:
		break;
	}
}

bool UHandleDisciple::HasEquipment(USect* sect, int32 disIndex, EEquipmentType type) {
	switch (type)
	{
	case EEquipmentType::Weapon:
		return UHandleEquipment::HasEquipment(sect->disciples[disIndex].weapon);
		break;
	case EEquipmentType::Artifact:
		return UHandleEquipment::HasEquipment(sect->disciples[disIndex].artifact);
		break;
	case EEquipmentType::HiddenWeapon:
		return UHandleEquipment::HasEquipment(sect->disciples[disIndex].hiddenWeapon);
		break;
	default:
		return false;
		break;
	}
}

bool UHandleDisciple::RarityCanLearn(const FDisciple& dis, const FLaw& law) {
	if (uint8(law.rarity) >= uint8(dis.rarity))
		return true;
	else
		return false;
}

bool UHandleDisciple::CanUseElixirs(FDisciple dis) {
	if (dis.yearAteElixirs == 5 || dis.ateElixirs == 100)
		return false;
	else
		return true;
}

void UHandleDisciple::UseElixirs(USect* sect, int32 disIndex, FElixirs elixirs) {
	sect->disciples[disIndex].UseElixirs(elixirs);
	int32* temp = sect->elixirs.Find(elixirs);
	if(temp != nullptr)
		*temp -= 1;
}

bool UHandleDisciple::UseRarityPill(USect* sect, int32 disIndex, FElixirs elixirs) {
	int32* num = sect->elixirs.Find(elixirs);
	if (num != nullptr) {
		if (*num == 0)
			return false;

		*num -= 1;
		int32 random = FMath::RandRange(1, 100);
		EDiscipleRarityType r = sect->disciples[disIndex].rarity;
		switch (r)
		{
		case EDiscipleRarityType::SonofEra:
			return false;
			break;
		case EDiscipleRarityType::Genius:
			if (random == 1) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::SonofEra);
				return true;
			}
			break;
		case EDiscipleRarityType::Extraordinary:
			if (random <= 5) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Genius);
				return true;
			}
			break;
		case EDiscipleRarityType::Outstanding:
			if (random <= 20) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Extraordinary);
				return true;
			}
			break;
		case EDiscipleRarityType::Excellent:
			if (random <= 40) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Outstanding);
				return true;
			}
			break;
		case EDiscipleRarityType::Normal:
			if (random <= 70) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Excellent);
				return true;
			}
			break;
		default:
			return false;
			break;
		}
	}
	return false;
}

void UHandleDisciple::SortElixirs(USect* sect, int32 disIndex) {
	sect->disciples[disIndex].usedElixirs.KeySort([](FElixirs A, FElixirs B) {
		return A.id < B.id;
	});
}

bool UHandleDisciple::CanLearnLaw(USect* sect, int32 disIndex, FLaw law) {
	for (int32 i = 0; i < 5; i++) {
		if (sect->disciples[disIndex].laws[i].id == law.id) {
			return false;
		}
	}
	return true;
}

void UHandleDisciple::LearnLaw(USect* sect, int32 disIndex, FLaw law, int32 index) {
	FText log = FText();
	if (UHandleLaw::HasLaw(sect->disciples[disIndex].laws[index])) {
		log = UDiscipleMessage::LearnNewLaw(sect->disciples[disIndex].laws[index]);
		sect->disciples[disIndex].logs.Add(log);
	}

	sect->disciples[disIndex].laws[index] = law;
	log = UDiscipleMessage::LearnLaw(law);
	sect->disciples[disIndex].logs.Add(log);
}

TArray<FLaw> UHandleDisciple::GetLaws(FDisciple dis) {
	return dis.laws;
}

int32 UHandleDisciple::GetCultivateSpeed(USect* sect, FDisciple dis) {
	return sect->speed + dis.cultivateSpeed;
}

bool UHandleDisciple::IsMarried(FDisciple dis) {
	return dis.married;
}

void UHandleDisciple::Marry(USect* sect, int32 index, FWife wife) {
	sect->disciples[index].wife = wife;
	sect->disciples[index].Marry();
	FText str = UDiscipleMessage::GetMarry(wife.surname, wife.name);
	sect->disciples[index].logs.Add(str);
}

void UHandleDisciple::Divorce(USect* sect, int32 index) {
	FWife temp = sect->disciples[index].wife;
	FText str = UDiscipleMessage::GetDivorce(temp.surname, temp.name);
	sect->disciples[index].logs.Add(str);
	sect->disciples[index].Divorce();
}

TArray<FWife> UHandleDisciple::GetWifes() {
	TArray<FWife> wifes;
	wifes.SetNum(3);
	for (auto& i : wifes)
		i.Create();
	return wifes;
}

int32 UHandleDisciple::GetH5(FDisciple dis) {
	int32 value = dis.health;
	float buff = 1.0;
	// 獲取裝備%數加成
	buff += dis.weapon.GetHP();
	buff += dis.artifact.GetHP();
	buff += dis.hiddenWeapon.GetHP();

	// 獲取性格加成
	switch (dis.personality) {
	case EPersonality::Careful:
		buff += 0.15;
		break;
	case EPersonality::Timid:
		buff -= 0.10;
		break;
	default:
		break;
	}

	// 獲取出身背景加成
	switch (dis.background)
	{
	case EBackground::Noble:
		buff += 0.05;
		break;
	case EBackground::Royal:
		buff += 0.10;
		break;
	default:
		break;
	}

	value *= buff * dis.wife.buff;
	value += dis.weapon.GetH5();
	value += dis.artifact.GetH5();
	value += dis.hiddenWeapon.GetH5();
	return value;
}

int32 UHandleDisciple::GetA5(FDisciple dis) {
	int32 value = dis.attack;
	float buff = 1.0;
	buff += dis.weapon.GetAP();
	buff += dis.artifact.GetAP();
	buff += dis.hiddenWeapon.GetAP();

	// 獲取性格加成
	switch (dis.personality) {
	case EPersonality::Ferocious:
		buff += 0.15;
		break;
	case EPersonality::Kindness:
		buff -= 0.10;
	case EPersonality::Timid:
		buff -= 0.10;
		break;
	default:
		break;
	}

	// 獲取出身背景加成
	switch (dis.background)
	{
	case EBackground::Military:
		buff += 0.15;
		break;
	case EBackground::Noble:
		buff += 0.05;
		break;
	case EBackground::Royal:
		buff += 0.10;
		break;
	default:
		break;
	}

	value *= buff * dis.wife.buff;
	value += dis.weapon.GetA5();
	value += dis.artifact.GetA5();
	value += dis.hiddenWeapon.GetA5();
	return value;
}

int32 UHandleDisciple::GetD5(FDisciple dis) {
	int32 value = dis.defense;
	float buff = 1.0;
	buff += dis.weapon.GetDP();
	buff += dis.artifact.GetDP();
	buff += dis.hiddenWeapon.GetDP();

	// 獲取性格加成
	switch (dis.personality) {
	case EPersonality::Timid:
		buff -= 0.10;
		break;
	default:
		break;
	}

	// 獲取出身背景加成
	switch (dis.background)
	{
	case EBackground::Military:
		buff += 0.05;
		break;
	case EBackground::Noble:
		buff += 0.05;
		break;
	case EBackground::Royal:
		buff += 0.10;
		break;
	default:
		break;
	}

	value *= buff * dis.wife.buff;
	value += dis.weapon.GetD5();
	value += dis.artifact.GetD5();
	value += dis.hiddenWeapon.GetD5();
	return value;
}

int32 UHandleDisciple::GetHealth(FDisciple dis) {
	int32 health = GetH5(dis) * 5;
	health += dis.weapon.GetHealth();
	health += dis.artifact.GetHealth();
	health += dis.hiddenWeapon.GetHealth();
	for (auto& i : dis.laws)
		health += UHandleLaw::GetHealth(i);

	return health;
}

int32 UHandleDisciple::GetDamage(FDisciple dis) {
	int32 damage = GetA5(dis) * 5;
	damage += dis.weapon.GetAttack();
	damage += dis.artifact.GetAttack();
	damage += dis.hiddenWeapon.GetAttack();
	for (auto& i : dis.laws)
		damage += UHandleLaw::GetDamage(i);

	return damage;
}

int32 UHandleDisciple::GetDefense(FDisciple dis) {
	int32 defense = GetD5(dis) * 5;
	defense += dis.weapon.GetDefense();
	defense += dis.artifact.GetDefense();
	defense += dis.hiddenWeapon.GetDefense();
	for (auto& i : dis.laws)
		defense += UHandleLaw::GetDefense(i);

	return defense;
}

int32 UHandleDisciple::GetCP(FDisciple dis) {
	int32 p = dis.criticalP;
	if (dis.personality == EPersonality::Cruel)
		p += 10;
	p += dis.weapon.GetCP();
	p += dis.artifact.GetCP();
	p += dis.hiddenWeapon.GetCP();
	return p;
}

float UHandleDisciple::GetCS(FDisciple dis) {
	float p = dis.criticalStrike;
	p += dis.weapon.GetCS();
	p += dis.artifact.GetCS();
	p += dis.hiddenWeapon.GetCS();
	return p;
}

FText UHandleDisciple::AfterBattle(USect* sect, int32 index) {
	TArray<int32> attribute;
	for (int32 i = 0; i < 3; i++) {
		int32 random = FMath::RandRange(1, 10);
		attribute.Add(random);
	}
	sect->disciples[index].health += attribute[0];
	sect->disciples[index].attack += attribute[1];
	sect->disciples[index].defense += attribute[2];
	return UDiscipleMessage::GetAfterBattle(sect->disciples[index], attribute);
}

bool UHandleDisciple::IsSonofEra(FDisciple dis) {
	return dis.rarity == EDiscipleRarityType::SonofEra ? true : false;
}

FText UDiscipleMessage::LearnLaw(FLaw& law) {
	FString str = "";
	TArray<FStringFormatArg> args = {FStringFormatArg(GetNowYear()), FStringFormatArg(law.name.ToString()) };
	str = Read(uint8(law.rarity));
	str = FString::Format(*str, args);
	
	return FText::FromString(*str);
}

FText UDiscipleMessage::LearnNewLaw(FLaw& law) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(GetNowYear()), FStringFormatArg(law.name.ToString()),};
	str = Read(uint8(law.rarity) + 7);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::LawToLimit(FLaw& law) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(GetNowYear()), FStringFormatArg(law.name.ToString()), };
	str = Read(uint8(law.rarity) + 14);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::LevelUp(int32 level) {
	const char* path = "DataTable'/Game/DataTable/Message/DisLevel.DisLevel'";
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(GetNowYear())};
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FReadStr* data = pDataTable->FindRow<FReadStr>(FName(*FString::FromInt(level)), "");
		if (data != NULL) {
			str = data->str;
			str = FString::Format(*str, args);
		}
	}
	return FText::FromString(*str);
}

FText UDiscipleMessage::GetMarry(FText& name1, FText& name2) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(GetNowYear()), FStringFormatArg(name1.ToString()),
	FStringFormatArg(name2.ToString()) };
	str = Read(21);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::GetDivorce(FText& name1, FText& name2) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(GetNowYear()), FStringFormatArg(name1.ToString()),
	FStringFormatArg(name2.ToString()) };
	str = Read(22);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::GetAfterBattle(FDisciple& dis, TArray<int32> attribute) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(dis.surname.ToString()), 
		FStringFormatArg(dis.name.ToString()),  FStringFormatArg(attribute[0]),
		FStringFormatArg(attribute[1]), FStringFormatArg(attribute[2]) };

	str = Read(23);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

