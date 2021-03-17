// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmemtUi.h"
#include "MyGameInstance.h"

UEquipmemtUi::UEquipmemtUi(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

bool UEquipmemtUi::Initialize() {
	if (!Super::Initialize())
		return false;
	
	equipments.SetNum(9);

	equipments[0] = Cast<UInventoryUi>((GetWidgetFromName)("Helmet"));
	equipments[1] = Cast<UInventoryUi>((GetWidgetFromName)("Armor"));
	equipments[2] = Cast<UInventoryUi>((GetWidgetFromName)("Necklace"));
	equipments[3] = Cast<UInventoryUi>((GetWidgetFromName)("Gloves"));
	equipments[4] = Cast<UInventoryUi>((GetWidgetFromName)("Weapon"));
	equipments[5] = Cast<UInventoryUi>((GetWidgetFromName)("RightRing"));
	equipments[6] = Cast<UInventoryUi>((GetWidgetFromName)("LeftRing"));
	equipments[7] = Cast<UInventoryUi>((GetWidgetFromName)("Belt"));
	equipments[8] = Cast<UInventoryUi>((GetWidgetFromName)("Shoes"));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	TArray<FItem> items = MyGameInstance->GetEquipment();

	for (int i = 0; i < 9; i++) {
		equipments[i]->SetIndex(i);
		equipments[i]->SetItem(items[i]);
	}
	
	return true;
}
