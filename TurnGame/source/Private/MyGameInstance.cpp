// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/FileManager.h"
#include "InventoryUi.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyBPLibrary.h"
#include "MyDatabase.h"

static uint8* ReadFile(IPlatformFile& PlatformFile, FString path, uint32& len) {
	IFileHandle* FileHandle = PlatformFile.OpenRead(*path);
	if (FileHandle) {
		len = (uint32)FileHandle->Size();
		uint8* buf = new uint8[len];

		FileHandle->Read(buf, len);

		// Close the file again
		delete FileHandle;

		return buf;
	}

	return nullptr;
}

UMyGameInstance::UMyGameInstance() :state("main", this) {

}

void UMyGameInstance::Init() {

	items.SetNum(100);
	equipments.SetNum(9);

	state.onInitEvent.AddUObject(this, &UMyGameInstance::LuaStateInitCallback);
	state.init();

	state.setLoadFileDelegate([](const char* fn, FString& filepath)->TArray<uint8> {

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		FString path = FPaths::ProjectContentDir();
		FString filename = UTF8_TO_TCHAR(fn);
		path /= "Lua";
		path /= filename.Replace(TEXT("."), TEXT("/"));

		TArray<uint8> Content;
		TArray<FString> luaExts = { UTF8_TO_TCHAR(".lua"), UTF8_TO_TCHAR(".luac") };
		for (auto& it : luaExts) {
			auto fullPath = path + *it;

			FFileHelper::LoadFileToArray(Content, *fullPath);
			if (Content.Num() > 0) {
				filepath = fullPath;
				return MoveTemp(Content);
			}
		}

		return MoveTemp(Content);
	});
}

void UMyGameInstance::Shutdown() {
	state.close();
}

static int32 PrintLog(NS_SLUA::lua_State* L) {
	FString str;
	size_t len;
	const char* s = luaL_tolstring(L, 1, &len);
	if (s) str += UTF8_TO_TCHAR(s);
	NS_SLUA::Log::Log("PrintLog %s", TCHAR_TO_UTF8(*str));
	return 0;
}

void UMyGameInstance::LuaStateInitCallback() {
	NS_SLUA::lua_State* L = state.getLuaState();
	lua_pushcfunction(L, PrintLog);
	lua_setglobal(L, "PrintLog");
}

TMap<TSubclassOf<UGameplayAbility>, int> UMyGameInstance::GetSkills() const {
	return skills;
}

void UMyGameInstance::AddNewAbility(TSubclassOf<UGameplayAbility> newAbility, int ID) {
	skills.Emplace(newAbility, ID);
	skills.ValueSort([](const int& A, const int& B) {
		return A < B;
	});
}

bool UMyGameInstance::IsInventoryFull() {
	bool bIsFull = true;

	for (auto& i : items)
		if (i.IsEmpty()) {
			bIsFull = false;
			break;
		}

	return bIsFull;
}

void UMyGameInstance::AddItem(FItem newItem) {

	newItem.CreateItemProperty();
	/*
	AMyDatabase * db = (AMyDatabase*) GetWorld()->SpawnActor(AMyDatabase::StaticClass());

	db->MyHTTPMethod(newItem.name.ToString(), newItem.GetRarity());

	db->Destroy();
	db = NULL;
	*/
	for (auto& item : items) {
		if (item.IsEmpty()) {
			item = newItem;
			break;
		}
		if (item.IsSameItem(newItem.GetID()) && item.CanOverlap()) {
			if (item.GetQuantity() + newItem.GetQuantity() <= GMaxItemQuantity) {
				item.AddQuantity(newItem.GetQuantity());
				break;
			}
			else {
				int total = item.GetQuantity() + newItem.GetQuantity();
				item.SetQuantity(GMaxItemQuantity);
				newItem.SetQuantity(total - GMaxItemQuantity);
			}

		}
	}
}

void UMyGameInstance::SetItemIndex(FItem newItem, int index) {
	items[index] = newItem;
}

void UMyGameInstance::DeleteItem(int index) {
	FItem temp;
	items[index] = temp;
}

TArray<FItem> UMyGameInstance::GetItems() const {
	return items;
}

TMap<int, FItem> UMyGameInstance::GetPotions() {
	TMap<int, FItem> potions;
	for (int i = 0; i < items.Num(); i++)
		if (items[i].IsPotion())
			potions.Emplace(i, items[i]);
	return potions;
}

void UMyGameInstance::UsePotion(int index) {
	ABaseCharacter* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (items[index].IsHPPotion()) {
		float playerHp = player->GetHealth() + items[index].attribute.health;
		if (playerHp > player->GetMaxHealth())
			player->SetHealth(player->GetMaxHealth());
		else
			player->SetHealth(playerHp);
	}
	else {
		float playerMp = player->GetMana() + items[index].attribute.mana;
		if (playerMp > player->GetMaxMana())
			player->SetMana(player->GetMaxMana());
		else
			player->SetMana(playerMp);
	}


	items[index].AddQuantity(-1);
	if (items[index].GetQuantity() == 0)
		DeleteItem(index);
}

FItem UMyGameInstance::WearEquipment(FItem equipment) {

	/*
	Helmet		= 0
	Armor		= 1
	Necklace	= 2
	Gloves		= 3
	Weapon		= 4
	LeftRing	= 5
	RightRing	= 6
	Belt		= 7
	Shoes		= 8
*/

	equipment.hasEquipped = true;

	if (equipment.IsHelmet())
		Swap(equipment, equipments[0]);

	else if (equipment.IsArmor())
		Swap(equipment, equipments[1]);

	else if (equipment.IsNecklace())
		Swap(equipment, equipments[2]);

	else if (equipment.IsGloves())
		Swap(equipment, equipments[3]);

	else if (equipment.IsWeapon())
		Swap(equipment, equipments[4]);

	else if (equipment.IsRing()) {
		// 左側の指輪は空なら、直接置く。
		// 左側もうあるなら、右側の指輪を換える
		if (equipments[5].IsEmpty())
			Swap(equipment, equipments[5]);
		else
			Swap(equipment, equipments[6]);
	}
		
	else if (equipment.IsBelt())
		Swap(equipment, equipments[7]);

	else
		Swap(equipment, equipments[8]);

	FMyAttributeSet temp;
	attributeSet = temp;

	for (auto& i : equipments)
		attributeSet = attributeSet + i.attribute;

	equipment.hasEquipped = false;
	return equipment;
}

bool UMyGameInstance::TakeOffEquipment(int index) {
	if (!IsInventoryFull()) {
		equipments[index].hasEquipped = false;
		AddItem(equipments[index]);
		DeleteEquipment(index);
		return true;
	}
	return false;
}

void UMyGameInstance::SellItem(int index, int quantity) {
	FItem& temp = items[index];
	cash += temp.GetPrice() * quantity;
	temp.SetQuantity(temp.GetQuantity() - quantity);
}

int UMyGameInstance::GetCash() const {
	return cash;
}

void UMyGameInstance::DeleteEquipment(int index) {
	FItem temp;
	equipments[index] = temp;
}

FMyAttributeSet UMyGameInstance::GetAttributeSet() const {
	return attributeSet;
}

TArray<FItem> UMyGameInstance::GetEquipment() const {
	return equipments;
}

void UMyGameInstance::PlayerGetExp(int min, int max) {
	AddExp(min, max);
	if (CanLevelUp()) {
		SubExp(GetLevelUpExp());
		IncreaseLevelUpExp();
		LevelUp();
	}
}

void UMyGameInstance::AddExp(int min, int max) {
	exp += GetRandomInt(min, max);
}

void UMyGameInstance::SubExp(int value) {
	exp -= value;
}

int UMyGameInstance::GetExp() const {
	return exp;
}

bool UMyGameInstance::CanLevelUp() {
	return exp >= levelUpExp ? true : false;
}

int UMyGameInstance::GetLevelUpExp() const {
	return levelUpExp;
}

void UMyGameInstance::IncreaseLevelUpExp() {
	levelUpExp += 20;
}

void UMyGameInstance::LevelUp() {
	level += 1;
}

int UMyGameInstance::GetLevel() const {
	return level;
}

void UMyGameInstance::Arrange() {
	TArray<ArrangeList> list;
	FindNotFull(list);
	Assign(list);
	SortItems();
}

void UMyGameInstance::FindNotFull(TArray<ArrangeList>& list) {
	int index = 0;
	for (auto& i : items) {

		int quantity = i.GetQuantity();

		// アイテムがある
		if (!i.IsEmpty()) {

			if (i.CanOverlap() && quantity < GMaxItemQuantity) {
				if (list.Num() == 0) {
					ArrangeList temp;
					temp.SetID(i.GetID());
					temp.Append(index);
					list.Emplace(temp);
				}

				else {

					for (auto& j : list) {
						// このアイテムもうある
						if (j.ID == i.GetID())
							j.Append(index);

						else {
							ArrangeList temp;
							temp.SetID(i.GetID());
							temp.Append(index);
							list.Emplace(temp);
						}
					}
				}
			}
		}

		index++;

	}
}

void UMyGameInstance::Assign(TArray<ArrangeList>& list) {
	for (auto& i : list) {

		// このアイテムの合計数量を計算する
		int total = 0;
		for (auto& j : i.index)
			total += items[j].GetQuantity();

		// アイテムを割り当てる
		for (auto& j : i.index) {
			// アイテムがないなら、この位置をクリアする。
			if (total == 0)
				DeleteItem(j);

			// 今、アイテムの数量は最大値より少ない
			else if (total < GMaxItemQuantity) {
				items[j].SetQuantity(total);
				total = 0;
			}

			// 今、アイテムの数量は最大値より多い
			// だから、アイテムの数量は最大値を引く
			else {
				items[j].SetQuantity(GMaxItemQuantity);
				total -= GMaxItemQuantity;
			}
		}
	}
}

void UMyGameInstance::SortItems() {
	items.Sort([](const FItem& A, const FItem& B) {
		// アイテムのIDが同じ
		if (A.GetID() == B.GetID()) {
			// 重ねられない
			//アイテムのレア度でソート
			if (!A.CanOverlap())
				return A.GetRarity() < B.GetRarity();
			//アイテムの数量でソート
			else
				return A.GetQuantity() > B.GetQuantity();
		}
		//アイテムのIDでソート
		else
			return A.GetID() < B.GetID();
	});
}

