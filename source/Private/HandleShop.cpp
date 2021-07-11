// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleShop.h"
#include "HandleEquipment.h"

int32 UHandleShop::GetEquipmentPrice(FEquipment equipment) {
	return int32(equipment.price * 1.2);
}

bool UHandleShop::CanBuyEquipment(USect* sect, FEquipment equipment) {
	if (sect->spiritStone >= GetEquipmentPrice(equipment))
		return true;
	else
		return false;
}

bool UHandleShop::CanAddEquipment(USect* sect, int32 index) {
	FEquipment temp = sect->shop.equips[index];
	bool canAdd = UHandleEquipment::CanAddEquipment(sect, temp.type);
	return canAdd;
}

void UHandleShop::BuyEquipment(USect* sect, int32 index) {
	FEquipment temp = sect->shop.equips[index];
	UHandleEquipment::AddSingleEquipment(sect, temp);
	sect->spiritStone = sect->spiritStone - GetEquipmentPrice(temp);
	sect->shop.equips[index].attribute.id = 0;
}

bool UHandleShop::CanBuyLaw(USect* sect, int32 index) {
	if (sect->spiritStone >= sect->shop.laws[index].price)
		return true;
	else
		return false;
}

void UHandleShop::BuyLaw(USect* sect, int32 index) {
	FLaw temp = sect->shop.laws[index];
	sect->hadLaws.Emplace(temp);
	sect->spiritStone -= temp.price;
	sect->shop.laws[index].id = 0;
	for (int32 i = 0; i < sect->noGetLaws.Num(); i++) {
		if (temp.id == sect->noGetLaws[i].id) {
			sect->noGetLaws.RemoveAt(i);
			break;
		}
	}
}

bool UHandleShop::CanBuySpiritBeast(USect* sect, int32 index) {
	if (sect->spiritStone >= sect->shop.spiritBeasts[index].price)
		return true;
	else
		return false;
}

bool UHandleShop::CanAddSpiritBeast(USect* sect) {
	return sect->spiritBeasts.Num() <= 30 ? true : false;
}

void UHandleShop::AddSpiritBeast(USect* sect, int32 index) {
	FSpiritBeast temp = sect->shop.spiritBeasts[index];
	sect->spiritBeasts.Emplace(temp);
	sect->spiritStone -= temp.price;
	sect->shop.spiritBeasts.RemoveAt(index);
}

