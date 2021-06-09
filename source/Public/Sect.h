// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "SpiritBeast.h"
#include "Facility.h"
#include <functional> // std::functional
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

	void SetFacility();

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

	UFUNCTION(BlueprintCallable)
	// �[�^�̤l��U���˳ƩΥ[�J�s���˳�
	void AddRemoveEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// �i�H�[�J�˳ƶ�
	bool CanAddEquipment(UEquipment* equipment);

	UFUNCTION(BlueprintCallable)
	// �[�J�s���\�k
	void AddLaw();

	UFUNCTION(BlueprintCallable)
	//�[�J�s���F�~
	void AddSpiritBeast();

	UFUNCTION(BlueprintCallable)
	// �[�^�̤l���׽m���\�k�Υ[�J�s���\�k
	void AddRemoveLaw(UCultivationLaw* law);

	UFUNCTION(BlueprintCallable)
	// �i�H�[�J�\�k��
	bool CanAddLaw(UCultivationLaw* law);

	UFUNCTION(BlueprintCallable)
	// ����Ҧ��]�I
	TArray<FFacility> GetFacilities();

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
	// ����Ҧ��F�~
	TArray<USpiritBeast*> GetSpiritBeasts();

	UFUNCTION(BlueprintCallable)
	// �����˳�
	void RemoveEquipment(UEquipment* equipment, int32 index);

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

	void AddAttribute(int32& attribute, std::function<int32(UEliteDisciple*)> Get);

	UFUNCTION(BlueprintCallable)
	// ����̲ק���
	int32 GetFinallyAttack();

	UFUNCTION(BlueprintCallable)
	// ����̲ץͩR
	int32 GetFinallyHealth();

	UFUNCTION(BlueprintCallable)
	// ����̲ר��m
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

	UFUNCTION(BlueprintCallable)
	// ����F��
	int32 GetSpiritStone() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �̤l
	TArray<UEliteDisciple*> eliteDisciples;

	// uobject�إߦW�ټƦr
	int32 eliteDiscipleNums = 0;
	int32 equipmentNums = 0;
	int32 lawNums = 0;
	int32 spiritBeastNums = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �F��
	int32 spiritStone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �ħ�
	int32 medicinalMaterials;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �Z��
	TArray<UEquipment*> weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �k�_
	TArray<UEquipment*> artifacts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �t��
	TArray<UEquipment*> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �׽m�k
	TArray<UCultivationLaw*> cultivationLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// ����k
	TArray<UCultivationLaw*> workoutLaws;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �Z��
	TArray<UCultivationLaw*> attackSkills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �F�~
	TArray<USpiritBeast*> spiritBeasts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// �]�I
	TArray<FFacility> facilities;

};

//void AddAttribute(int32& attribute, int32 start, int32 end, TArray<UEliteDisciple*>& disciples, std::function<int32(UEliteDisciple*)> Get);
