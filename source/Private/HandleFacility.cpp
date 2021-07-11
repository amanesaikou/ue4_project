// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleFacility.h"

bool UHandleFacility::HasLevelUp(FFacility facility) {
	return facility.hasLevelUp;
}

int32 UHandleFacility::GetLevelUpCost(FFacility facility) {
	// 獲取升級花費
	return facility.GetLevelUpCost();
}

bool UHandleFacility::CanLevelUp(USect* sect, int32 index) {
	int32 cash = sect->spiritStone;
	FFacility temp = sect->facilities[index];
	// 錢夠且設施還沒滿等
	if (cash >= temp.GetLevelUpCost() && !temp.IsLevelMax())
		return true;
	else
		return false;
}

void UHandleFacility::LevelUp(USect* sect, int32 index) {
	sect->spiritStone -= sect->facilities[index].GetLevelUpCost();
	sect->facilities[index].LevelUp();
	switch (index)
	{
	case 0:
		sect->ySpiritStone += sect->facilities[index].value;
		break;
	case 1:
		sect->yMedicinalMaterials += sect->facilities[index].value;
	case 3:
		break;
	default:
		break;
	}
}

int32 UHandleFacility::HowManyCanMake(USect* sect, FFacility facility) {
	int32 cost = facility.value - facility.level * 50;
	return sect->medicinalMaterials / cost;
}
