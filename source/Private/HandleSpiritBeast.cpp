// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleSpiritBeast.h"

void UHandleSpiritBeast::AddSpiritBeast(USect* sect) {
	const char* path = "DataTable'/Game/DataTable/SpiritBeast/SpiritBeast.SpiritBeast'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		int32 which = FMath::RandRange(0, rowNames.Num() - 1);
		FSpiritBeast* data = pDataTable->FindRow<FSpiritBeast>(rowNames[which], "");
		if (data != NULL) {
			data->SetPassive();
			data->Setting();
			sect->spiritBeasts.Emplace(*data);
		}
	}
}

FSpiritBeast UHandleSpiritBeast::CreateSB() {
	const char* path = "DataTable'/Game/DataTable/SpiritBeast/SpiritBeast.SpiritBeast'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		int32 which = FMath::RandRange(0, rowNames.Num() - 1);
		FSpiritBeast* data = pDataTable->FindRow<FSpiritBeast>(rowNames[which], "");
		if (data != NULL) {
			data->SetPassive();
			data->Setting();
			return *data;
		}
	}
	return FSpiritBeast();
}

FPassiveSkill UHandleSpiritBeast::GetPassive(FSpiritBeast sb) {
	return sb.passive;
}

uint8 UHandleSpiritBeast::GetBlood(FSpiritBeast sb) {
	return uint8(sb.blood);
}

int32 UHandleSpiritBeast::GetAge(FSpiritBeast sb) {
	return sb.age;
}

int32 UHandleSpiritBeast::GetHealth(FSpiritBeast sb) {
	return sb.health;
}

int32 UHandleSpiritBeast::GetAttack(FSpiritBeast sb) {
	return sb.attack;
}

int32 UHandleSpiritBeast::GetDefense(FSpiritBeast sb) {
	return sb.defense;
}

bool UHandleSpiritBeast::HasBloodPill(USect* sect) {
	FElixirs temp;
	temp.id = 77;
	int32* num = sect->elixirs.Find(temp);
	if (num == nullptr || *num == 0)
		return false;
	else
		return true;
}

int32 UHandleSpiritBeast::GetBloodPillNum(USect* sect) {
	FElixirs temp;
	temp.id = 77;
	int32* num = sect->elixirs.Find(temp);
	if (num == nullptr)
		return 0;
	else
		return *num;
}

bool UHandleSpiritBeast::IsDiamond(FSpiritBeast sb) {
	return sb.blood == EBlood::Diamond ? true : false;
}

bool UHandleSpiritBeast::RiseBlood(USect* sect, int32 index) {
	FElixirs temp;
	temp.id = 77;
	int32* num = sect->elixirs.Find(temp);
	if (num != nullptr) {
		*num -= 1;
		int32 random = FMath::RandRange(1, 100);
		EBlood r = sect->spiritBeasts[index].blood;
		switch (r)
		{
		case EBlood::Diamond:
			return false;
			break;
		case EBlood::Platinum:
			if (random <= 5) {
				sect->spiritBeasts[index].blood = EBlood::Diamond;
				return true;
			}
			break;
		case EBlood::Gold:
			if (random <= 15) {
				sect->spiritBeasts[index].blood = EBlood::Diamond;
				return true;
			}
			break;
		case EBlood::Silver:
			if (random <= 25) {
				sect->spiritBeasts[index].blood = EBlood::Gold;
				return true;
			}
			break;
		case EBlood::Bronze:
			if (random <= 40) {
				sect->spiritBeasts[index].blood = EBlood::Silver;
				return true;
			}
			break;
		case EBlood::BlackIron:
			if (random <= 60) {
				sect->spiritBeasts[index].blood = EBlood::Bronze;
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
