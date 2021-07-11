// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleBattle.h"
#include "HandleDisciple.h"

int32 UHandleBattle::ComputePlayerDamage(USect* sect) {
	int32 damage = 0;
	for (auto& i : sect->disciples)
		damage += i.GetDamage();

	return damage;
}

TArray<int32> UHandleBattle::TwoDisBattle(FDisciple player, FDisciple enemy, int32 playerH, int32 enemyH) {
	int32 pDamage = player.GetDamage();

	if (pDamage - UHandleDisciple::GetDefense(enemy) * 1.2 < 500) {
		enemyH -= 500;
	}
	else {
		enemyH = enemyH - (pDamage - UHandleDisciple::GetDefense(enemy) * 1.2);
	}
	int32 eDamage = enemy.GetDamage();
	if (eDamage - UHandleDisciple::GetDefense(player) * 1.2 < 500) {
		playerH -= 500;
	}
	else {
		playerH = playerH - (eDamage - UHandleDisciple::GetDefense(player) * 1.2);
	}
	
	TArray<int32> remaining = { playerH, enemyH };
	return remaining;
}
