// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "slua.h"
#include "Sect.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOP_API UMyGameInstance : public UGameInstance {

	GENERATED_BODY()

public:
	UMyGameInstance();

	///** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	//virtual void Init() override;

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	//virtual void Shutdown() override;

	//UFUNCTION()
	//void LuaStateInitCallback();

	// create global state, freed on app exit
	//NS_SLUA::LuaState state;

	void CreateEnemys();

	UFUNCTION(BlueprintCallable)
	USect* GetSect();

	UFUNCTION(BlueprintCallable)
	TArray<FCommonAttribute> GetEnemys();

	UFUNCTION(BlueprintCallable)
	void SetEnemyIndex(int32 index);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyIndex();

	UFUNCTION(BlueprintCallable)
	FCommonAttribute GetEnemy();

protected:
/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UDisciple>> disciples;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCultivationLaw* cultivationLaw;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCultivationLaw*> cultivationLaws;

*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USect* sect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCommonAttribute> enemys;

	int32 enemyIndex = 0;
};
	
