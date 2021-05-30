// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "Sect.generated.h"

/**
 * 
 */

// ����
UCLASS(BlueprintType)
class DEVELOP_API USect : public UObject {
	GENERATED_BODY()

public:

	// �غc�l
	USect();

	UFUNCTION(BlueprintCallable)
	// �[�J�s���̤l
	void AddEliteDisciple();

	UFUNCTION(BlueprintCallable)
	// �۶ҧ̤l
	void EmployEliteDisciple();

	UFUNCTION(BlueprintCallable)
	// �i�H�۶Ҷ�
	bool CanEmployDisciple();

	UFUNCTION(BlueprintCallable)
	// �X�v�̤l
	void ExpelDisciple(int32 index);

	UFUNCTION(BlueprintCallable)
	// �i�H�X�v�̤l�� �X�v�̤l�᪫�~�|�[�^�� ���ˬd�O�_�W�L���~�ƶq�W�� 
	bool CanExpelDisciple(int32 index);

	UFUNCTION(BlueprintCallable)
	// �[�J�s���˳�
	void AddEquipment();

	//UFUNCTION(BlueprintCallable)
	// �[�^�̤l��U���˳�
	void AddEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// �[�J�s���\�k
	void AddLaw();

	//UFUNCTION(BlueprintCallable)
	// �[�^�̤l��U���\�k
	void AddLaw(UCultivationLaw* law);

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��̤l
	TArray<UEliteDisciple*> GetEliteDisciples();

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��Z��
	TArray<UEquipment*> GetWeapons();

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��k�_
	TArray<UEquipment*> GetArtifacts();

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��t��
	TArray<UEquipment*> GetHiddenWeapons();

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��׽m�k
	TArray<UCultivationLaw*> GetCultivationLaws();

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��v��k
	TArray<UCultivationLaw*> GetWorkoutLaws();

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��Z��
	TArray<UCultivationLaw*> GetAttackSkills();

	UFUNCTION(BlueprintCallable)
	// �����Z��
	void RemoveWeapon(int32 index);

	UFUNCTION(BlueprintCallable)
	// �����k�_
	void RemoveArtifact(int32 index);

	UFUNCTION(BlueprintCallable)
	// �����t��
	void RemoveHiddenWeapon(int32 index);

	UFUNCTION(BlueprintCallable)
	// �����׽m�k
	void RemoveCultivationLaw(int32 index);

	UFUNCTION(BlueprintCallable)
	// ��������k
	void RemoveWorkoutLaw(int32 index);

	UFUNCTION(BlueprintCallable)
	// �����Z��
	void RemoveAttackSkill(int32 index);

	UFUNCTION(BlueprintCallable)
	// �ϥ��F��
	void UseSpiritStone(int32 cost);

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyAttack();

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyHealth();

	UFUNCTION(BlueprintCallable)
	int32 GetFinallyDefense();

	UFUNCTION(BlueprintCallable)
	// �̤l�Ƨ�
	void DiscipleSort();

	UFUNCTION(BlueprintCallable)
	// �\�k�Ƨ�
	void CultivationLawSort(int32 index);

	UFUNCTION(BlueprintCallable)
	// �˳ƱƧ�
	void EquipmentSort(int32 index);

	UFUNCTION(BlueprintCallable)
	// �W�[�F��
	void AddSpiritStone(int32 num);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEliteDisciple*> eliteDisciples;

	// uobject�إߦW�ټƦr
	int32 eliteDiscipleNums = 0;
	int32 equipmentNums = 0;
	int32 lawNums = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 money;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 spiritStone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEquipment*> weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEquipment*> artifacts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEquipment*> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> cultivationLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> workoutLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> attackSkills;

};
