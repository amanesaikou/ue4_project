// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "HandleSpiritBeast.h"
#include <thread>
using std::thread;

FShop::FShop() {

}

void FShop::UpdateGood(TArray<FLaw> noGet) {
	UpdateEquipments();
	UpdateLaws(noGet);
	spiritBeasts.Empty();

	for (int32 i = 0; i < 30; i++) {
		FSpiritBeast temp = UHandleSpiritBeast::CreateSB();
		spiritBeasts.Emplace(temp);
	}
}

void FShop::UpdateEquipments() {
	equips.Empty();

	for (int32 i = 0; i < 30; i++) {
		FEquipment temp;
		temp.Create();
		equips.Emplace(temp);
	}

	equips.Sort([](const FEquipment& A, const FEquipment& B) {
		if (A.type == B.type)
			return A.rarity < B.rarity;
		return A.type < B.type;
	});
}

void FShop::UpdateLaws(TArray<FLaw>& noGet) {
	laws.Empty();

	while (laws.Num() < 30 && noGet.Num() != 0) {
		int32 law = FMath::RandRange(0, noGet.Num() - 1);
		laws.Emplace(noGet[law]);
		noGet.RemoveAt(law);
	}

	laws.Sort([](const FLaw& A, const FLaw& B) {
		return A.id < B.id;
	});
}
