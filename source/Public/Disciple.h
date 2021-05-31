// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "Disciple.generated.h"

/**
 * 
 */

// �׭^�̤l
UCLASS(BlueprintType)
class DEVELOP_API UEliteDisciple : public UObject {

	GENERATED_BODY()

public:

	UEliteDisciple();

	// �]�w�̤l�m�W ���ק�
	void DecideName();

	// �M�w�̤l���
	void DecideRarity();

	// �M�w�̤l�R�c�ƶq
	void DecideLifePalace();

	// �M�w�̤l�P���ƶq
	void DecideStar();

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	// ������
	UFUNCTION(BlueprintCallable)
	EDiscipleRarityType GetRarity() const;
	
	// ������W��
	UFUNCTION(BlueprintCallable)
	FString GetRarityName() const;

	UFUNCTION(BlueprintCallable)
	//
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	//
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	//
	int32 GetFinallyDefense() const;

	// �R�c�P�P���[��
	float GetBuff() const;

	// ��˳�
	UFUNCTION(BlueprintCallable)
	void WearEquipment(const TArray<UEquipment*>& weapons, int32 index);
	void WearWeapon(const TArray<UEquipment*>& weapons, int32 index);
	void WearArtifact(const TArray<UEquipment*>& artifacts, int32 index);
	void WearHiddenWeapon(const TArray<UEquipment*>& hiddenWeapons, int32 index);

	// �ϥΥ\�k
	UFUNCTION(BlueprintCallable)
	void UseLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	void UseCultivationLaw(const TArray<UCultivationLaw*>& laws, int32 index);
	void UseWorkoutLaw(const TArray<UCultivationLaw*>& laws, int32 index);
	void UseAttackSkill(const TArray<UCultivationLaw*>& laws, int32 index);

	void RemoveAll();

	UFUNCTION(BlueprintCallable)
	void RemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	void RemoveLaw(UCultivationLaw* law);

	class UMyGameInstance* GetGameInstance() const;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetArtifact() const;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetHiddenWeapon() const;

	UFUNCTION(BlueprintCallable)
	UCultivationLaw* GetCultivationLaw() const;

	UFUNCTION(BlueprintCallable)
	UCultivationLaw* GetWorkoutLaw() const;

	UFUNCTION(BlueprintCallable)
	UCultivationLaw* GetAttackSkill() const;

	UFUNCTION(BlueprintCallable)
	int32 GetLifePalace() const;

	UFUNCTION(BlueprintCallable)
	FString GetLifePalaceTitle() const;

	UFUNCTION(BlueprintCallable)
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
	FString GetStarTitle() const;

	// �̤l���
	EDiscipleRarityType rarity;

protected:

	// �׭^�̤l���ݩ� 
	FCommonAttribute attriute;

	// �T��˳�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UEquipment* weapon;			// �Z��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UEquipment* artifact;		// �k�_
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UEquipment* hiddenWeapon;	// �t��

	// �T�إ\�k
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* cultivationLaw; // �ߪk
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* workoutLaw;	 // ����k
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* attackSkill;	 // �Z��

	// �R�c�� �̦h13
	int32 lifePalace;

	// �P���� �̦h9
	int32 stars;

};

//template void UEliteDisciple::Apply(const TArray<UEquipment*>& items, int32 index, UEquipment* item);
//template void UEliteDisciple::Apply(const TArray<UCultivationLaw*>& items, int32 index, UCultivationLaw* item);