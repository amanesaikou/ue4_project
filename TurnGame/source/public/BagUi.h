// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserWidget.h"
#include "InventoryUi.h"
#include "BagUi.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTURNGAME_API UBagUi : public ULuaUserWidget
{
	GENERATED_BODY()

public:

	UBagUi(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	void SetUi();

	UFUNCTION(BlueprintCallable)
	void Arrange();

	class UButton* ArrangeButton;

	class UScrollBox* ScrollBox;

	class UWrapBox* Items;

	TArray<UInventoryUi*> itemUi;

};
