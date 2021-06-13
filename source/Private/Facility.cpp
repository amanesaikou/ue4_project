// Fill out your copyright notice in the Description page of Project Settings.


#include "Facility.h"

FFacility::FFacility() {
	value = 0;
}

void FFacility::LevelUp() {
	level += 1;
}

bool FFacility::CanLevelUp() {
	return level == 10 ? false : true;
}

void FFacility::SetValue(int32 newValue) {
	value = newValue;
}

FString FFacility::GetName() const {
	return name;
}

int32 FFacility::GetValue() const {
	return value;
}

int32 FFacility::GetLevel() const {
	return level;
}
