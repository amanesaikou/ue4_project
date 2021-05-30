// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Math/Color.h"
#include "MyBPLibrary.generated.h"

// �׽m�k����
UENUM(BlueprintType)
enum class ECultivationType : uint8 {
	CultivationLaw	= 0,	// �ߪk
	WorkoutLaw		= 1,	// ����k
	AttackSkill		= 2,	// �Z��
};

// �˳ƺ���
UENUM(BlueprintType)
enum class EEquipmentType : uint8 {
	Weapon			= 0,	// �Z��
	Artifact		= 1,	// �k�_
	HiddenWeapon	= 2,	// �t��
};

// �D��}����
UENUM(BlueprintType)
enum class EItemRarityType : uint8 {
	Immortal		= 0, // �P��		1%
	Holy			= 1, // �t��		3%
	Sky				= 2, // �ѯ�		5%
	Earth			= 3, // �a��		8%
	Mysterious		= 4, // �ȯ�		14%
	Yellow			= 5, // ����		24%
	Human			= 6, // �H��		45%
};

// �̤l�}����
UENUM(BlueprintType)
enum class EDiscipleRarityType : uint8 {
	SonofEra		= 0,	// �������l	1%
	Genius			= 1,	// ��ź		4%
	Extraordinary	= 2,	// �D�Z		9%
	Outstanding		= 3,	// �ǥX		12%
	Excellent		= 4,	// �u�q		26%
	Normal			= 5,	// �@��		48%
};

// �@�θ�Ƶ��c
USTRUCT(BlueprintType)
struct FCommonData : public FTableRowBase {

	GENERATED_BODY()

	// �غc�l
	FCommonData();

	// �\�k�h�� ���~�}���׵�
	UPROPERTY(BlueprintReadWrite)
	FString name;

	// �׽m�F�۪�O ���~�}���׾��v��
	UPROPERTY(BlueprintReadWrite)
	int32 number;

	FString GetName() const;

	int32 GetNumber() const;

};

// ���~����
USTRUCT(BlueprintType)
struct FDataTablePath : public FTableRowBase {

	GENERATED_BODY()

	// �غc�l
	FDataTablePath();

	// �ɮ׸��|
	UPROPERTY(BlueprintReadWrite)
	FString tablePath;

	const char* GetPath() const;

};

// �U�ئr���Ƶ��c
USTRUCT(BlueprintType)
struct FCommonString : public FTableRowBase {

	GENERATED_BODY()

	// �غc�l
	FCommonString();

	// 
	UPROPERTY(BlueprintReadWrite)
	FString str;

	FString GetString() const;

};

/**
 * 
 */
 // �B�z�U��enum�����O
UCLASS()
class DEVELOP_API UTypeBPLibrary : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:
	// �M�w���~�}���׻P�̤l��誺�ҪO
	template<class T>
	static T DecideRarity(const char* tablePath);

	// �ھھ��v����������}����
	static uint8 GetRarityIndex(TArray<int32>& probabilities);

	// �M�w�׷Ҫk�P�˳ƺ������ҪO
	template<class T>
	static T DecideType();

	// ������~�}���שΧ̤l��誺�W�٪��ҪO
	template<class T>
	static FString GetRarityName(const char* tablePath, T rarity);

	UFUNCTION(BlueprintCallable)
	static FLinearColor GetDiscipleColor(EDiscipleRarityType rarity);

	static bool IsSonofEra(EDiscipleRarityType rarity);
	static bool IsGenius(EDiscipleRarityType rarity);
	static bool IsExtraordinary(EDiscipleRarityType rarity);
	static bool IsOutstanding(EDiscipleRarityType rarity);
	static bool IsExcellent(EDiscipleRarityType rarity);
	static bool IsNormal(EDiscipleRarityType rarity);
	/*
	static bool IsImmortal(EItemRarityType rarity);
	static bool IsHoly(EItemRarityType rarity);
	static bool IsSky(EItemRarityType rarity);
	static bool IsEarth(EItemRarityType rarity);
	static bool IsImmortal(EItemRarityType rarity);
	static bool IsImmortal(EItemRarityType rarity);
	static bool IsImmortal(EItemRarityType rarity);
	*/
};

// ��ƶ��禡�w
//UCLASS()
class DEVELOP_API UDatasetBPLibrary {//: public UBlueprintFunctionLibrary {

	//GENERATED_BODY()

public:
	// ������v ���~�}���� �̤l��赥
	static TArray<int32> GetRarityProbability(const char* tablePath);

	// �����ƪ���|
	static const char* GetTablePath(const char* path, int32 index);
	//
	static FName FromIntToFName(int32 num);
};

class DEVELOP_API UPath {

public:
	// �\�k�h�������|
	static const char* GetLawLevelPath();

	// ���~�}���ת���|
	static const char* GetItemRarityPath();

	// �̤l������|
	static const char* GetDiscipleRarityPath();

	// �\�k�ݩʸ��|��
	static const char* GetLawTablePath();

	// �˳��ݩʸ��|��
	static const char* GetEquipmentTablePath();

	// �˳��ݩʸ��|��
	static const char* GetLifePalaceTitlePath();

	// �˳��ݩʸ��|��
	static const char* GetStarTitlePath();
};

// ��Ҥ�
//template FString UTypeBPLibrary::GetRarityName(const char* tablePath, int32 rarity);
template FString UTypeBPLibrary::GetRarityName(const char* tablePath, EItemRarityType rarity);
template FString UTypeBPLibrary::GetRarityName(const char* tablePath, EDiscipleRarityType rarity);

template int32 UTypeBPLibrary::DecideRarity(const char* tablePath);
template EItemRarityType UTypeBPLibrary::DecideRarity(const char* tablePath);
template EDiscipleRarityType UTypeBPLibrary::DecideRarity(const char* tablePath);

template ECultivationType UTypeBPLibrary::DecideType();
template EEquipmentType UTypeBPLibrary::DecideType();