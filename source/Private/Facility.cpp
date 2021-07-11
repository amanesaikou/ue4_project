// Fill out your copyright notice in the Description page of Project Settings.


#include "Facility.h"

FFacility::FFacility() {

}

int32 FFacility::GetLevelUpCost() {
	// 靈石花費每一等+1000
	return (level + 1) * 1000;
}

bool FFacility::IsLevelMax() {
	return level == 10 ? true : false;
}

void FFacility::LevelUp() {
	++level;
	hasLevelUp = true;
}

void FFacility::Update() {
	hasLevelUp = false;
}
