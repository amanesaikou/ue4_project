// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#endif //PCH_H
/*
#ifdef IMPORT_DLL
#else
//#define DLL extern "C" _declspec(dllimport) 
#define DLL extern "C" _declspec(dllexport)
//extern "C"
#endif
*/

#ifdef DLL
#else
#define DLL _declspec(dllexport)
#endif

class DllLib {
public:
	DLL static int GetProperty(int value, int rarity, int random);

	DLL static float GetDamage(float sourceAttack, float sourceCS, float targetDefense, float random);
};

