// Fill out your copyright notice in the Description page of Project Settings.


#include "Firm.h"

UFirm::UFirm() {
	UpdateGoods();
}

void UFirm::UpdateGoods() {
	equipments.Empty();
	laws.Empty();
	spiritBeasts.Empty();
	for (int32 i = 0; i < 6; i++) {
		AddEquipment();
		AddLaw();
		AddSpiritBeast();
	}
}

void UFirm::AddEquipment() {
	FString objectName = "GoodEquipment";
	objectName.AppendInt(eNum++);
	UEquipment* temp = NewObject<UEquipment>(this, FName(*objectName));
	equipments.Emplace(temp);
}

void UFirm::AddLaw() {
	FString objectName = "GoodLaw";
	objectName.AppendInt(lNum++);
	UCultivationLaw* temp = NewObject<UCultivationLaw>(this, FName(*objectName));
	laws.Emplace(temp);
}

void UFirm::AddSpiritBeast() {
	FString objectName = "GoodSpiritBeast";
	objectName.AppendInt(sNum++);
	USpiritBeast* temp = NewObject<USpiritBeast>(this, FName(*objectName));
	spiritBeasts.Emplace(temp);
}

TArray<UEquipment*> UFirm::GetEquipments() {
	return equipments;
}

UEquipment* UFirm::GetEquipment(int32 index) {
	return equipments[index];
}

void UFirm::RemoveEquipment(int32 index) {
	equipments.RemoveAt(index);
}

TArray<UCultivationLaw*> UFirm::GetLaws() {
	return laws;
}

TArray<USpiritBeast*> UFirm::GetSpiritBeasts() {
	return spiritBeasts;
}
