// Fill out your copyright notice in the Description page of Project Settings.


#include "Disciple.h"
#include "Constant.h"
#include "HandleLaw.h"
#include "HandleDisciple.h"

FWife::FWife() {
	name = FText();
	appearance = EAppearance::SSS; 
	personality = EWPersonality::SS;
	buff = 1.0;
	speed = 0;
	criticalP = 0;
	criticalStrike = 0.0;
}

void FWife::Create() {
	DecideName();
	DecideAppearance();
	DecidePersonality();
}

void FWife::DecideName() {
	auto GetText = [](int32 choice) {
		const char* path = GetDiscipleNamePath(choice);
		if (path != nullptr) {
			UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
			if (pDataTable != NULL) {
				TArray<FName> rowNames = pDataTable->GetRowNames();
				int32 random = FMath::RandRange(0, rowNames.Num() - 1);
				FName row = FName(*FString::FromInt(random));
				FReadText* data = pDataTable->FindRow<FReadText>(row, "");
				if (data != NULL) {
					return data->str;
				}
			}
		}
		return FText();
	};
	surname = GetText(1);
	name = GetText(3);
}

void FWife::DecideAppearance() {
	TArray<int32> p = { 1, 4, 9, 17, 27, 40, 60, 73, 83, 91, 96, 99, 100 };
	int32 random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < p.Num(); i++) {
		if (random < p[i]) {
			appearance = EAppearance(i);
			break;
		}
	}
	int32 P = FMath::RandRange(1, 2);
	switch (appearance)
	{
	case EAppearance::SSS:
		SetBuff(0.2, 5, 0, 0.15);
		break;
	case EAppearance::SS:
		SetBuff(0.17, 4, 0, 0.13);
		break;
	case EAppearance::S:
		SetBuff(0.14, 3, 0, 0.11);
		break;
	case EAppearance::A:
		SetBuff(0.11, 2, 0, 0.09);
		break;
	case EAppearance::B:
		SetBuff(0.08, 1, 0, 0.07);
		break;
	case EAppearance::C:
		SetBuff(0.05, 0, 0, 0.05);
		break;
	case EAppearance::D:
		if(P == 1)
			SetBuff(0.05, 0, 0, 0.03);
		else
			SetBuff(-0.05, 0, 0, 0.03);
		break;
	case EAppearance::E:
		SetBuff(-0.05, 0, 5, 0.0);
		break;
	case EAppearance::F:
		SetBuff(-0.08, 4, 8, 0.0);
		break;
	case EAppearance::G:
		SetBuff(-0.11, 1, 11, 0.0);
		break;
	case EAppearance::H:
		SetBuff(-0.14, 1, 14, 0.0);
		break;
	case EAppearance::I:
		SetBuff(-0.17, 1, 17, 0.0);
		break;
	case EAppearance::J:
		SetBuff(-0.20, 1, 20, 0.0);
		break;
	default:
		break;
	}
	
}

void FWife::DecidePersonality() {
	int32 random = FMath::RandRange(0, 12);
	personality = EWPersonality(random);
	int32 P = FMath::RandRange(1, 2);
	switch (personality)
	{
	case EWPersonality::SSS:
		SetBuff(0.15, 2, 6, 0.05);
		break;
	case EWPersonality::SS:
		SetBuff(0.13, 2, 5, 0.05);
		break;
	case EWPersonality::S:
		SetBuff(0.11, 2, 4, 0.05);
		break;
	case EWPersonality::A:
		SetBuff(0.09, 1, 3, 0.05);
		break;
	case EWPersonality::B:
		SetBuff(0.07, 1, 2, 0.05);
		break;
	case EWPersonality::C:
		SetBuff(0.05, 1, 1, 0.05);
		break;
	case EWPersonality::D:
		if(P == 1)
			SetBuff(0.03, 0, 0, 0.03);
		else
			SetBuff(-0.03, 0, 0, 0.03);
		break;
	case EWPersonality::E:
		SetBuff(-0.05, 0, 2, 0.05);
		break;
	case EWPersonality::F:
		SetBuff(-0.07, 0, 4, 0.07);
		break;
	case EWPersonality::G:
		SetBuff(-0.09, 0, 6, 0.09);
		break;
	case EWPersonality::H:
		SetBuff(-0.11, 0, 8, 0.11);
		break;
	case EWPersonality::I:
		SetBuff(-0.13, 0, 10, 0.13);
		break;
	case EWPersonality::J:
		SetBuff(-0.15, 0, 12, 0.15);
		break;
	default:
		break;
	}
}

void FWife::SetBuff(float cbuff, int32 cspeed, int32 CP, float CS) {
	buff += cbuff;
	speed += cspeed;
	criticalP += CP;
	criticalStrike += CS;
}


FDisciple::FDisciple() {
	DecideRarity();
	DecideName();
	DecidePersonality();
	DecideBackground();
	DecideLifePalace();
	DecideStar();
	laws.SetNum(5);
	DecideAttribute();
}

void FDisciple::DecideRarity() {
	TArray<int32> rarityP = { 1, 5, 14, 26, 52, 100 };
	int32 random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < rarityP.Num(); i++) {
		if (random <= rarityP[i]) {
			rarity = EDiscipleRarityType(i);
			break;
		}
	}

}

void FDisciple::ResetRarity(EDiscipleRarityType r) {
	// 去除原來提供的屬性
	health -= lifePalace * 200;
	defense -= lifePalace * 60;
	attack -= star * 160;
	rarity = r;
	DecideLifePalace();
	DecideStar();
	// 加回提供的屬性
	health += lifePalace * 200;
	defense += lifePalace * 60;
	attack += star * 160;
	SetCultivateSpeed();
	if (married) {
		cultivateSpeed += wife.speed;
	}
}

void FDisciple::DecideName() {

	auto GetText = [](int32 choice) {
		const char* path = GetDiscipleNamePath(choice);
		if (path != nullptr) {
			UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
			if (pDataTable != NULL) {
				TArray<FName> rowNames = pDataTable->GetRowNames();
				int32 random = FMath::RandRange(0, rowNames.Num() - 1);
				FName row = FName(*FString::FromInt(random));
				FReadText* data = pDataTable->FindRow<FReadText>(row, "");
				if (data != NULL) {
					return data->str;
				}
			}
		}
			return FText();
	};
	surname = GetText(1);
	name = GetText(2);

}

void FDisciple::DecidePersonality() {
	int32 random = FMath::RandRange(0, 4);
	personality = EPersonality(random);
}

void FDisciple::DecideBackground() {
	TArray<int32> backgroundP = {25, 40, 55, 75, 80, 100};
	int32 random = FMath::RandRange(1, 100);
	int32 choice = 0;
	for (int32 i = 0; i < backgroundP.Num(); i++) {
		if (random <= backgroundP[i]) {
			choice = i;
			break;
		}
	}
	background = EBackground(choice);
}

void FDisciple::DecideLifePalace() {
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

void FDisciple::DecideStar() {
	switch (rarity)
	{
	case EDiscipleRarityType::SonofEra:
		star = FMath::RandRange(8, 9);
		break;
	case EDiscipleRarityType::Genius:
		star = FMath::RandRange(7, 8);
		break;
	case EDiscipleRarityType::Extraordinary:
		star = FMath::RandRange(5, 6);
		break;
	case EDiscipleRarityType::Outstanding:
		star = FMath::RandRange(3, 4);
		break;
	case EDiscipleRarityType::Excellent:
		star = FMath::RandRange(2, 3);
		break;
	case EDiscipleRarityType::Normal:
		star = FMath::RandRange(1, 2);
		break;
	default:
		break;
	}
}

void FDisciple::DecideAttribute() {
	SetCultivateSpeed();
	year = FMath::RandRange(18, 25);
	criticalP = 10;
	criticalStrike = 0.1;
	health += lifePalace * 200;
	defense += lifePalace * 60;
	attack += star * 160;
}

void FDisciple::SetCultivateSpeed() {
	int32 base = 20;
	cultivateSpeed = base + lifePalace + star;
}

void FDisciple::CultivateLaw(int32 speed) {
	// 修煉所有功法
	for (auto& i : laws) {
		if (UHandleLaw::HasLaw(i) && i.CanLevelUp()) {	// 此位置已有功法且還沒滿級
			i.exp += cultivateSpeed + speed;	// 進行修煉
			i.LevelUp();	// 檢查能否升級
			if (!i.CanLevelUp()) {	// 檢查完若升至10級添加記錄
				FText str = UDiscipleMessage::LawToLimit(i);
				logs.Add(str);
			}
	
		}
	}
}

void FDisciple::Practice() {
	// 檢查境界是否還沒到上限
	if (level < 10) {
		// 已可進階 嘗試進階
		if (practice >= GetNextExp()) {
			if (CanLevelUp()) {
				LevelUp();
			}
		}
		else {
		// 還不可進階 經過今年修煉滿足可進階就嘗試進階
			practice += cultivateSpeed;
			if (practice >= GetNextExp()) {
				if (CanLevelUp()) {
					LevelUp();
				}
			}
		}
	}
}

int32 FDisciple::GetNextExp() {
	TArray<int32> exps = { 220, 440, 1100, 1760, 2200, 3300, 4400, 8800, 11000, 22000};
	return exps[level];
}

bool FDisciple::CanLevelUp() {
	if (level < 3)
		return true;
	else {
		int32 random = FMath::RandRange(1, 100);
		if (random < 51)
			return true;
		else
			return false;
	}
}

void FDisciple::LevelUp() {
	practice -= GetNextExp();
	++level;
	FText str = UDiscipleMessage::LevelUp(level);
	logs.Add(str);
}

void FDisciple::Marry() {
	married = true;
	cultivateSpeed += wife.speed;
	criticalP += wife.criticalP;
	criticalStrike += wife.criticalStrike;
}

void FDisciple::Divorce() {
	cultivateSpeed -= wife.speed;
	criticalP -= wife.criticalP;
	criticalStrike -= wife.criticalStrike;
	married = false;
	FWife nWife;
	wife = nWife;
}

int32 FDisciple::GetDamage() {
	int32 damage = UHandleDisciple::GetDamage(*this);
	int32 cp = FMath::RandRange(1, 100);
	if (cp <= criticalStrike)
	 damage = damage * (1 + criticalStrike);
	
	if (background == EBackground::Outcast)
		damage *= 1.1;

	return damage;
}

void FDisciple::SetEnemy() {
	// 敵人穿裝備
	
	FEquipment w, a, h;
	w.Create(EEquipmentType::Weapon);
	a.Create(EEquipmentType::Artifact);
	h.Create(EEquipmentType::HiddenWeapon);
	weapon = w;
	artifact = a;
	hiddenWeapon = h;
	
	// 敵人修煉功法
	const char* path = "DataTable'/Game/DataTable/Law/Law.Law'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	for (int32 i = 0; i < 5; i++) {
		if (pDataTable != NULL) {
			//int32 law = FMath::RandRange(406, 552);
			int32 law = FMath::RandRange(0, 20);
			FLaw* temp = pDataTable->FindRow<FLaw>(FName(*FString::FromInt(law)), "");
			if (temp != NULL) {
				laws[i] = *temp;
			}
		}
	}
}

void FDisciple::UseElixirs(FElixirs elixirs) {
	int32* usedNum = usedElixirs.Find(elixirs);
	if (usedNum == nullptr) {
		usedElixirs.Emplace(elixirs, 1);
	}
	else
		*usedNum += 1;
	EElixirsType type = elixirs.type;
	switch (type)
	{
	case EElixirsType::Health:
		health += elixirs.value;
		break;
	case EElixirsType::Attack:
		attack += elixirs.value;
		break;
	case EElixirsType::Defense:
		defense += elixirs.value;
		break;
	case EElixirsType::All:
		health += elixirs.value;
		attack += elixirs.value;
		defense += elixirs.value;
		break;
	case EElixirsType::Rarity:
		break;
	default:
		break;
	}
	++ateElixirs;
	++yearAteElixirs;
}
