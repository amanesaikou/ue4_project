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

	// ����̤l���m��P�W�r�i��զX
	FString GetName(const char* path) const;

	// �]�w�̤l�Y�����ޭ�
	void SetImageIndex();

	UFUNCTION(BlueprintCallable)
	// ����̤l�Y�����ޭ�
	int32 GetImageIndex() const;

	// �M�w�̤l���
	void DecideRarity();

	// �M�w�̤l�R�c�ƶq
	void DecideLifePalace();

	// �M�w�̤l�P���ƶq
	void DecideStar();

	UFUNCTION(BlueprintCallable)
	// ����̤l�W��
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	// ������
	EDiscipleRarityType GetRarity() const;
	
	UFUNCTION(BlueprintCallable)
	// ������W��
	FString GetRarityName() const;

	UFUNCTION(BlueprintCallable)
	// ����̲ק���
	int32 GetFinallyAttack() const;

	UFUNCTION(BlueprintCallable)
	// ����̲ץͩR
	int32 GetFinallyHealth() const;

	UFUNCTION(BlueprintCallable)
	// ����̲ר��m
	int32 GetFinallyDefense() const;

	// �R�c�P�P���[��
	float GetBuff() const;

	UFUNCTION(BlueprintCallable)
	// ��˳�
	void WearEquipment(const TArray<UEquipment*>& weapons, int32 index);

	// ��Z��
	void WearWeapon(const TArray<UEquipment*>& weapons, int32 index);

	// ��k�_
	void WearArtifact(const TArray<UEquipment*>& artifacts, int32 index);

	// ��t��
	void WearHiddenWeapon(const TArray<UEquipment*>& hiddenWeapons, int32 index);

	// �׽m�\�k
	UFUNCTION(BlueprintCallable)
	void UseLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	// �׽m�׽m�k
	void UseCultivationLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	// �׽m����k
	void UseWorkoutLaw(const TArray<UCultivationLaw*>& laws, int32 index);

	// �׽m�Z��
	void UseAttackSkill(const TArray<UCultivationLaw*>& laws, int32 index);

	// ���������˳ƻP�\�k
	void RemoveAll();

	UFUNCTION(BlueprintCallable)
	// ��U�˳�
	void RemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// ���׽m
	void RemoveLaw(UCultivationLaw* law);

	// ���GameInstance
	class UMyGameInstance* GetGameInstance() const;

	UFUNCTION(BlueprintCallable)
	// ���o�Z��
	UEquipment* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	// ���o�k�_
	UEquipment* GetArtifact() const;

	UFUNCTION(BlueprintCallable)
	// ���o�t��
	UEquipment* GetHiddenWeapon() const;

	UFUNCTION(BlueprintCallable)
	// ���o�׽m�k
	UCultivationLaw* GetCultivationLaw() const;

	UFUNCTION(BlueprintCallable)
	// ���o����k
	UCultivationLaw* GetWorkoutLaw() const;

	UFUNCTION(BlueprintCallable)
	// ���o�Z��
	UCultivationLaw* GetAttackSkill() const;

	UFUNCTION(BlueprintCallable)
	// ����R�c�ƶq
	int32 GetLifePalace() const;

	UFUNCTION(BlueprintCallable)
	// ����R�c�ٸ�
	FString GetLifePalaceTitle() const;

	UFUNCTION(BlueprintCallable)
	// ����P���ƶq
	int32 GetStar() const;

	UFUNCTION(BlueprintCallable)
	// ����P���ٸ�
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
