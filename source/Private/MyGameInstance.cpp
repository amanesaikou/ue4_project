// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\MyGameInstance.h"
#include "..\Public\Constant.h"
#include "HandleDisciple.h"
#include "HandleEquipment.h"
#include "HandleSpiritBeast.h"

UMyGameInstance::UMyGameInstance() {
	SetYear(1);
	sect = NewObject<USect>(this, TEXT("sect"));
	int32 index = 0;
	FString objectName = "Enemy";
	for (int32 i = 0; i < 10; i++) {
		FString temp = objectName;
		FString name = TEXT("門派");
		name.AppendInt(i+1);
		temp.AppendInt(i);
		UEnemySect* eSect = NewObject<UEnemySect>(this, FName(*temp));
		eSect->Create();
		eSect->name = FText::FromString(name);
		enemys.Emplace(eSect);
	}
	for (int32 i = 0; i < 5; i++)
		UHandleDisciple::AddDisciple(sect);

	for (int32 i = 0; i < 100; i++)
		UHandleEquipment::AddEquipment(sect);
	for (int32 i = 0; i < 50; i++)
		UHandleSpiritBeast::AddSpiritBeast(sect);
}

void UMyGameInstance::AfterYear() {
	AfterAYear();
	sect->Update();
	for (auto& i : enemys)
		i->Update();
}

int32 UMyGameInstance::GetYear() {
	return GetNowYear();
}

UEnemySect* UMyGameInstance::GetEnemy(int32 index) {
	return enemys[index];
}
