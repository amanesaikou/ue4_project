// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryUi.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyBPLibrary.h"
#include <functional> // std::function

UInventoryUi::UInventoryUi(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

bool UInventoryUi::Initialize() {
	if (!Super::Initialize())
		return false;

	Border = Cast<UBorder>((GetWidgetFromName)("Border"));

	Icon = Cast<UImage>((GetWidgetFromName)("Icon"));

	Quantity = Cast<UTextBlock>((GetWidgetFromName)("Quantity"));

	return true;
}

void UInventoryUi::Clear() {
	FItem newItem;
	item = newItem;
	Icon->SetVisibility(ESlateVisibility::Hidden);
	Quantity->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryUi::SetItem(FItem newItem) {
	this->item = newItem;
	ShowItemData();
}

bool UInventoryUi::CanOverlap() {
	return item.CanOverlap();
}

void UInventoryUi::ShowItemData() {
	if (!item.IsEmpty()) {
		ShowImage();
		ShowQuantity();
	}
}

void UInventoryUi::ShowImage() {
	Icon->SetBrushFromTexture(item.GetIcon(), true);
	Icon->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryUi::ShowQuantity() {
	if (item.CanOverlap()) {
		FString temp = FString::FromInt(item.GetQuantity());
		FText quantity = FText::FromString(temp);
		Quantity->SetText(quantity);
		Quantity->SetVisibility(ESlateVisibility::Visible);
	}
}

int UInventoryUi::GetQuantity(){
	return item.GetQuantity();
}

void UInventoryUi::SubQuantity(int value) {
	item.SetQuantity(item.GetQuantity() - value);
}

void UInventoryUi::SetIndex(int i) {
	index = i;
}

FItem::FItem() {
	ID = 1000;
	name = FText::FromString("");
	icon = NULL;
	currentQuantity = 0;
	canOverlap = false;
	hasEquipped = false;
}

bool FItem::IsEmpty() {
	return ID == 1000 ? true : false;
}

bool FItem::IsSameItem(int checkID) {
	return ID == checkID ? true : false;
}

int FItem::GetID() const {
	return ID;
}

UTexture2D* FItem::GetIcon() {
	return icon;
}

int FItem::GetQuantity() const {
	return currentQuantity;
}

int FItem::GetPrice() {
	return price;
}

void FItem::SetQuantity(int value) {
	currentQuantity = value;
}

void FItem::AddQuantity(int value) {
	currentQuantity += value;
}

bool FItem::CanOverlap() const {
	return canOverlap == true ? true : false;
}

void FItem::CreateItemProperty() {
	if (IsUnknown())
		DecideRarity();
	if (GetItemType() < 8) {
		CreateProperty();
		DecidePrice();
	}
}

void FItem::DecideRarity() {
	int rare = GetRandomInt(1, 100);
	if (rare >= 1 && rare <= 70)
		rarity = ERarity::Normal;
	else if (rare >= 71 && rare <= 90)
		rarity = ERarity::Excellent;
	else if (rare >= 91 && rare <= 99)
		rarity = ERarity::Rare;
	else
		rarity = ERarity::Legend;
}

bool FItem::IsPotion() {
	if (IsHPPotion() || IsMPPotion())
		return true;
	else
		return false;
}

bool FItem::IsHelmet() {
	return itemType == EItemType::Helmet ? true : false;
}

bool FItem::IsArmor() {
	return itemType == EItemType::Armor ? true : false;
}

bool FItem::IsNecklace() {
	return itemType == EItemType::Necklace ? true : false;
}

bool FItem::IsGloves() {
	return itemType == EItemType::Gloves ? true : false;
}

bool FItem::IsWeapon() {
	return itemType == EItemType::Weapon ? true : false;
}

bool FItem::IsRing() {
	return itemType == EItemType::Ring ? true : false;
}

bool FItem::IsBelt() {
	return itemType == EItemType::Belt ? true : false;
}

bool FItem::IsShoes() {
	return itemType == EItemType::Shoes ? true : false;
}

bool FItem::IsHPPotion() {
	return itemType == EItemType::HPPotion ? true : false;
}

bool FItem::IsMPPotion() {
	return itemType == EItemType::MPPotion ? true : false;
}

uint8 FItem::GetItemType() const {
	return uint8(itemType);
}

uint8 FItem::GetRarity() const {
	return uint8(rarity);
}

bool FItem::IsUnknown() {
	return rarity == ERarity::Unknown ? true : false;
}

bool FItem::IsNormal() {
	return rarity == ERarity::Normal ? true : false;
}

bool FItem::IsExcellent() {
	return rarity == ERarity::Excellent ? true : false;
}

bool FItem::IsRare() {
	return rarity == ERarity::Rare ? true : false;
}

bool FItem::IsLegend() {
	return rarity == ERarity::Legend ? true : false;
}

//typedef int(*getadd)(int a, int b);

void FItem::CreateProperty() {
	FMyAttributeSet temp;
	uint8 r = GetRarity();

	auto GetValue = [&](int max, std::function<float(FMyAttributeSet&)> Get) {
		int value = Get(attribute);
		value = UMyBPLibrary::ComputeProperty(value, r, max);
		//value = value * r + GetRandomInt(1, value) + GetRandomInt(0, max);
		return value;
	};
	if (attribute.GetHealth() > 0.0) {
		int hp = GetValue(500, &FMyAttributeSet::GetHealth);
		temp.SetHealth(hp);
		temp.SetMaxHealth(hp);
	}
	if (attribute.GetMana() > 0.0) {
		int mp = GetValue(100, &FMyAttributeSet::GetMana);
		temp.SetMana(mp);
		temp.SetMaxMana(mp);
	}
	if (attribute.GetAttack() > 0.0) {
		int atk = GetValue(200, &FMyAttributeSet::GetAttack);
		temp.SetAttack(atk);
	}
	if (attribute.GetDefense() > 0.0) {
		int def = GetValue(50, &FMyAttributeSet::GetDefense);
		temp.SetDefense(def);
	}
	if (attribute.GetCriticalStrike() > 0.0) {
		float cs = attribute.GetDefense();
		cs = cs * r  + GetRandomInt(1, 3);
		temp.SetCriticalStrike(cs);
	}
	attribute = temp;
}

void FItem::DecidePrice() {
	int minPrice[4] = { 100, 500, 2000, 9000 };
	int maxPrice[4] = { 200, 800, 3000, 10000 };
	uint8 r = GetRarity();
	price = GetRandomInt(minPrice[r - 1], maxPrice[r - 1]);
}


void Swap(FItem& A, FItem& B) {
	FItem temp;
	temp = A;
	A = B;
	B = temp;
}

void ArrangeList::SetID(int itemID) {
	ID = itemID;
}

void ArrangeList::Append(int i) {
	index.Emplace(i);
}
