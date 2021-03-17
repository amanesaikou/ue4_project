// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUi.h"
#include "EquipmemtUi.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTURNGAME_API UEquipmemtUi : public UUserWidget
{
	GENERATED_BODY()

public:
	UEquipmemtUi(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	TArray<UInventoryUi*> equipments;
	
};
