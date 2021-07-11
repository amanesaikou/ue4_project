// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySect.h"

UEnemySect::UEnemySect() {
	name = FText();
	health = 0;
	attack = 0;
	defense = 0;
}

void UEnemySect::Create() {
	name = FText();
	health = 100000;
	attack = 50000;
	defense = 30000;
	for (int32 i = 0; i < 60; i++) {
		FDisciple temp;
		temp.SetEnemy();
		disciples.Emplace(temp);
	}
}

void UEnemySect::Update() {
	canGiveGift = true;
	canUseAlienate = true;
	canUseExplore = true;
	canCommunicate = true;
	if (disciples.Num() < 60) {
		int32 random = FMath::RandRange(1, 100);
		if (random <= 40) {
			FDisciple temp;
			temp.SetEnemy();
			disciples.Emplace(temp);
		}
	}
	// 讓敵人門派修煉功法
	for (auto& i : disciples) {
		i.CultivateLaw(0);
		if (i.logs.Num() > 0)
			i.logs.Empty();
	}
}

TArray<FDisciple> UEnemySect::GetFiveDis() {
	TArray<int32> num;
	TArray<int32> index;
	for (int32 i = 0; i < disciples.Num(); i++)
		num.Add(i);

	for (int32 i = 0; i < 5; i++) {
		int32 random = FMath::RandRange(0, num.Num() - 1);
		index.Add(num[random]);
		num.RemoveAt(random);
	}
	TArray<FDisciple> dis;
	for (int32 i = 0; i < 5; i++)
		dis.Emplace(disciples[index[i]]);

	return dis;
}

bool UEnemySect::GiveGift(USect* sect) {
	canGiveGift = false;
	int32 random = FMath::RandRange(1, 100);
	if (random <= 40) {
		return false;
	}
	else {
		sect->spiritStone -= 5000;
		friendly += 10;
		return true;
	}
}

bool UEnemySect::CanAlienate() {
	if (friendly >= 60 && canUseAlienate)
		return true;
	else
		return false;
}

bool UEnemySect::Alienate(int32 level) {
	friendly -= 60;
	canUseAlienate = false;
	int32 random = FMath::RandRange(1, 100);
	int32 p = 0;
	if (level > sectLevel)
		p = 80;
	else if (level == sectLevel)
		p = 60;
	else
		p = 20;

	if (random <= p) {
		Expel();
		return true;
	}
	else
		return false;
}

void UEnemySect::Expel() {
	int32 expelDis = FMath::RandRange(1, 3);

	for (int32 i = 0; i < expelDis; i++) {
		int32 random = FMath::RandRange(0, disciples.Num() - 1);
		disciples.RemoveAt(random);
	}
}

bool UEnemySect::CanExplore() {
	if (friendly >= 80 && canUseExplore)
		return true;
	else
		return false;
}

bool UEnemySect::Explore(int32 level) {
	friendly -= 80;
	canUseExplore = false;
	int32 random = FMath::RandRange(1, 100);
	int32 p = 0;
	if (level > sectLevel)
		p = 100;
	else if (level == sectLevel)
		p = 70;
	else
		p = 50;

	if (random <= p) {
		Expel();
		return true;
	}
	else
		return false;
}
