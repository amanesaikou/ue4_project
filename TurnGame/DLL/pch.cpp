// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
#include <cmath>

int DllLib::GetProperty(int value, int rarity, int random) {
	return value * rarity + random;
}

float DllLib::GetDamage(float sourceAttack, float sourceCS, float targetDefense, float random) {
	if (sourceCS >= random)
		sourceAttack *= 2;
	float temp = sourceAttack - targetDefense;
	return floor(temp);
}
