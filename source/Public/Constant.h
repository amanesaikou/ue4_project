// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
 // 功法層次表的路徑
constexpr const char* gLawLevel = "DataTable'/Game/StarterContent/Datatable/LawLevel/LawLevel.LawLevel'";

// 物品稀有度表路徑
constexpr const char* gItemRarity = "DataTable'/Game/StarterContent/Datatable/Rarity/ItemRarity.ItemRarity'";

// 弟子資質表路徑
constexpr const char* gDiscipleRarity = "DataTable'/Game/StarterContent/Datatable/Rarity/DiscipleRarity.DiscipleRarity'";

// 功法屬性路徑表
constexpr const char* gLawTablePath = "DataTable'/Game/StarterContent/Datatable/ItemTablePath/LawTablePath.LawTablePath'";

// 裝備屬性路徑表
constexpr const char* gEquipmentTablePath = "DataTable'/Game/StarterContent/Datatable/ItemTablePath/EquipmentTablePath.EquipmentTablePath'";

// 命宮路徑表
constexpr const char* gLifePalaceTitle = "DataTable'/Game/StarterContent/Datatable/Title/LifePalaceTitle.LifePalaceTitle'";

// 星辰路徑表
constexpr const char* gStarTitle = "DataTable'/Game/StarterContent/Datatable/Title/StarTitle.StarTitle'";

// 姓氏路徑表
constexpr const char* gSurname = "DataTable'/Game/StarterContent/Datatable/Name/Surname.Surname'";

// 名字路徑表
constexpr const char* gName = "DataTable'/Game/StarterContent/Datatable/Name/Name.Name'";

// 靈獸路徑表
constexpr const char* gSpiritBeast = "DataTable'/Game/StarterContent/Datatable/SpiritBeast/SpiritBeast.SpiritBeast'";

// 靈獸天賦表
constexpr const char* gPassiveSkill = "DataTable'/Game/StarterContent/Datatable/SpiritBeast/PassiveSkill.PassiveSkill'";

// 設施路徑表
constexpr const char* gFacility = "DataTable'/Game/StarterContent/Datatable/Facility/Facility.Facility'";

// 靈石、藥材最大數量
constexpr int32 gLimit = 2000000000;

// 血脈升級所需值
constexpr int32 gBloodLine[] = { 200, 1000, 5000 };

// 弟子上限
constexpr int32 gDiscipleLimit = 60;

// 物品上限
constexpr int32 gItemLimit = 80;

// 靈獸上限
constexpr int32 gSpiritBeastLimit = 24;

// 強化等級上限
constexpr int32 gEnhanceLimit = 20;

// 精煉等級上限
constexpr int32 gRefineLimit = 15;

// 修煉層次上限
constexpr int32 gLawLevelLimit = 20;