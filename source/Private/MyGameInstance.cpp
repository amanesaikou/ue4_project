// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance() {
	sect = NewObject<USect>(this, TEXT("sect"));
	CreateEnemys();
}

void UMyGameInstance::CreateEnemys() {
	FCommonAttribute temp;
	temp.SetName("AAAA");
	temp.SetAttack(100000);
	temp.SetHealth(1000000);
	temp.SetDefense(100000);
	for (int32 i = 0; i < 10; i++)
		enemys.Emplace(temp);
}

USect* UMyGameInstance::GetSect() {
	return sect;
}

TArray<FCommonAttribute> UMyGameInstance::GetEnemys() {
	return enemys;
}

void UMyGameInstance::SetEnemyIndex(int32 index) {
	enemyIndex = index;
}

int32 UMyGameInstance::GetEnemyIndex() {
	return enemyIndex;
}

FCommonAttribute UMyGameInstance::GetEnemy() {
	return enemys[enemyIndex];
}

void UMyGameInstance::AfterAYear() {
	++years;
}

int32 UMyGameInstance::GetYears() const {
	return years;
}
