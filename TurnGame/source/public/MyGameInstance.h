// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "slua.h"
#include "BaseCharacter.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/Texture2D.h"
#include "InventoryUi.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTURNGAME_API UMyGameInstance : public UGameInstance
{

	GENERATED_BODY()

public:
	UMyGameInstance();

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

	UFUNCTION()
	void LuaStateInitCallback();

	// create global state, freed on app exit
	NS_SLUA::LuaState state;

	// 全てのスキルを取得する
	UFUNCTION(BlueprintCallable)
	TMap<TSubclassOf<UGameplayAbility>, int> GetSkills() const;

	// 新しいスキルを増加する
	UFUNCTION(BlueprintCallable)
	void AddNewAbility(TSubclassOf<UGameplayAbility> newAbility, int ID);

	// インベントリがいっぱいか
	bool IsInventoryFull();

	// アイテムを増加する
	UFUNCTION(BlueprintCallable)
	void AddItem(FItem newItem);

	//　アイテムの索引を設定する。
	UFUNCTION(BlueprintCallable)
	void SetItemIndex(FItem newItem, int index);

	// アイテムを削除する
	UFUNCTION(BlueprintCallable)
	void DeleteItem(int index);

	// 全てのアイテムを取得する
	UFUNCTION(BlueprintCallable)
	TArray<FItem> GetItems() const;

	// 全てのアイテムを取得する
	UFUNCTION(BlueprintCallable)
	TMap<int, FItem> GetPotions(); 

	// 全ての薬を取得する
	UFUNCTION(BlueprintCallable)
	void UsePotion(int index);

	// 装備を着る
	UFUNCTION(BlueprintCallable)
	FItem WearEquipment(FItem equipment);

	// 装備を脱ぐ
	UFUNCTION(BlueprintCallable)
	bool TakeOffEquipment(int index);

	// アイテムを売る
	UFUNCTION(BlueprintCallable)
	void SellItem(int index, int quantity);

	// プレイヤーのお金を取得する
	UFUNCTION(BlueprintCallable)
	int GetCash() const;

	// 装備を削除する
	void DeleteEquipment(int index);

	// 属性値を取得する
	FMyAttributeSet GetAttributeSet() const;

	// 全ての装備を取得する
	TArray <FItem> GetEquipment() const;

	// プレイヤーが経験値を得た
	UFUNCTION(BlueprintCallable)
	void PlayerGetExp(int min, int max);

	// 経験値を足す
	void AddExp(int min, int max);

	//　経験値を引く
	void SubExp(int value);

	// 経験値を取得する
	UFUNCTION(BlueprintCallable)
	int GetExp() const;

	// レベルアップできるか
	bool CanLevelUp();

	// レベルアップできる経験値を取得する
	UFUNCTION(BlueprintCallable)
	int GetLevelUpExp() const;

	// レベルアップできる経験値を増加する
	void IncreaseLevelUpExp();
	
	//　レベルアップ
	void LevelUp();

	UFUNCTION(BlueprintCallable)
	// レベルを取得する
	int GetLevel() const;

	void Arrange();

	void FindNotFull(TArray<ArrangeList>& list);

	void Assign(TArray<ArrangeList>& list);

	void SortItems();

private:
	FMyAttributeSet attributeSet;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TSubclassOf<UGameplayAbility>, int> skills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FItem> items;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray <FItem> equipments;

	int exp = 0;

	int levelUpExp = 50;

	int level = 1;

	int cash = 0;
};
