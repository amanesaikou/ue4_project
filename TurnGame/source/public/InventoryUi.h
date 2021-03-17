// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserWidget.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "BaseCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "InventoryUi.generated.h"

/**
 * 
 */

// アイテムの最大量
constexpr int GMaxItemQuantity = 5;

// アイテムの種類
UENUM(BlueprintType)
enum class EItemType : uint8 {
	Helmet		= 0		UMETA(DisplayName = "Helmet"),
	Armor		= 1		UMETA(DisplayName = "Armor"),
	Necklace	= 2		UMETA(DisplayName = "Necklace"),
	Gloves		= 3		UMETA(DisplayName = "Gloves"),
	Weapon		= 4		UMETA(DisplayName = "Weapon"),
	Ring		= 5		UMETA(DisplayName = "Ring"),
	Belt		= 6		UMETA(DisplayName = "Belt"),
	Shoes		= 7		UMETA(DisplayName = "Shoes"),
	HPPotion	= 8		UMETA(DisplayName = "HPPotion"),
	MPPotion	= 9		UMETA(DisplayName = "MPPotion"),
	Material	= 10	UMETA(DisplayName = "Material"),
};

// アイテムのレア度
UENUM(BlueprintType)
enum class ERarity : uint8 {
	Unknown		= 0		UMETA(DisplayName = "Unknown"),
	Normal		= 1		UMETA(DisplayName = "Normal"),
	Excellent	= 2		UMETA(DisplayName = "Excellent"),
	Rare		= 3		UMETA(DisplayName = "Rare"),
	Legend		= 4		UMETA(DisplayName = "Legend"),
};

USTRUCT(BlueprintType)
struct FItem : public FTableRowBase {

	GENERATED_BODY()
	
	// コンストラクタ
	FItem();

	// 空か
	bool IsEmpty();

	// 同じものか
	bool IsSameItem(int checkID);

	// アイテムのIDを取得する
	int GetID() const;

	// アイテムのアイコンを取得する
	UTexture2D* GetIcon();

	// アイテムの数量を取得する
	int GetQuantity() const;

	// アイテムの販売価格を取得する
	int GetPrice();

	// アイテムの数量を設定する
	void SetQuantity(int value);

	// アイテムの数量を足す
	void AddQuantity(int value);

	// アイテムを重ねられるか
	bool CanOverlap() const;

	// アイテムの属性値を作成する
	void CreateItemProperty();

	// アイテムのレア度を決める
	void DecideRarity();

	// 薬か
	bool IsPotion();

	//　アイテムの種類はどれか
	bool IsHelmet();
	bool IsArmor();
	bool IsNecklace();
	bool IsGloves();
	bool IsWeapon();
	bool IsRing();
	bool IsBelt();
	bool IsShoes();
	bool IsHPPotion();
	bool IsMPPotion();

	uint8 GetItemType() const;
	uint8 GetRarity() const;

	// アイテムのレア度はどれか
	bool IsUnknown();
	bool IsNormal();
	bool IsExcellent();
	bool IsRare();
	bool IsLegend();

	void CreateProperty();
	void DecidePrice();

	UPROPERTY(BlueprintReadWrite)
	int ID;
	
	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* icon;

	UPROPERTY(BlueprintReadWrite)
	int currentQuantity;

	UPROPERTY(BlueprintReadWrite)
	bool canOverlap;

	UPROPERTY(BlueprintReadWrite)
	bool hasEquipped;

	UPROPERTY(BlueprintReadWrite)
	EItemType itemType;

	UPROPERTY(BlueprintReadWrite)
	ERarity rarity;

	UPROPERTY(BlueprintReadWrite)
	int price;

	UPROPERTY(BlueprintReadWrite)
	FMyAttributeSet attribute;

};

struct ArrangeList {
	int ID;
	TArray<int> index;

	void SetID(int itemID);
	void Append(int i);
};


// アイテムを交換する
void Swap(FItem& A, FItem& B);

UCLASS()
class MAGICTURNGAME_API UInventoryUi : public ULuaUserWidget
{
	GENERATED_BODY()

public:

	UInventoryUi(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	class UBorder* Border;

	class UImage* Icon;

	class UTextBlock* Quantity;

	// アイテムのダークを削除する
	UFUNCTION(BlueprintCallable)
	void Clear();

	// アイテムを設定する
	UFUNCTION(BlueprintCallable)
	void SetItem(FItem newItem);

	// アイテムを重ねられるか
	UFUNCTION(BlueprintCallable)
	bool CanOverlap();

	// アイテムのデータを示す
	void ShowItemData();

	// アイテムのアイコンを示す
	void ShowImage();

	// アイテムの数量を示す
	UFUNCTION(BlueprintCallable)
	void ShowQuantity();

	UFUNCTION(BlueprintCallable)
	int GetQuantity();

	UFUNCTION(BlueprintCallable)
	void SubQuantity(int value);

	// Uiの索引を設定する
	void SetIndex(int i);

	UPROPERTY(BlueprintReadWrite)
	FItem item;

	UPROPERTY(BlueprintReadWrite)
	int index;
};
