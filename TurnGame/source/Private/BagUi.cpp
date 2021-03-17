// Fill out your copyright notice in the Description page of Project Settings.


#include "BagUi.h"
#include <thread>
#include <ctime>
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "InventoryUi.h"
#include "MyGameInstance.h"

UBagUi::UBagUi(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

bool UBagUi::Initialize() {
	if (!Super::Initialize())
		return false;
	
	ArrangeButton = Cast<UButton>((GetWidgetFromName)("ArrangeButton"));
	ArrangeButton->OnClicked.AddDynamic(this, &UBagUi::Arrange);

	ScrollBox = Cast<UScrollBox>((GetWidgetFromName)("ScrollBox"));

	Items = Cast<UWrapBox>((GetWidgetFromName)("Items"));

	itemUi.SetNum(100);

	SetUi();
	
	return true;
}

void UBagUi::SetUi() {

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	TArray<FItem> items = MyGameInstance->GetItems();

	for (int i = 0; i < 100; i++) {
		itemUi[i] = CreateWidget<UInventoryUi>(GetGameInstance(),
			LoadClass<UInventoryUi>(NULL, TEXT("WidgetBlueprint'/Game/Ui/Inventory/BP_Inventory.BP_Inventory_C'")));

		Items->AddChildToWrapBox(itemUi[i]);
		itemUi[i]->SetIndex(i);
		itemUi[i]->SetItem(items[i]);

	}

}

void UBagUi::Arrange() {
	Items->ClearChildren();
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	std::thread arrange(&UMyGameInstance::Arrange, MyGameInstance);
	arrange.join();
	SetUi();
}
