// Fill out your copyright notice in the Description page of Project Settings.


#include "Sect.h"
#include "HandleEquipment.h"

USect::USect() {
	ReadLaws();
	ReadTreasures();
	spiritStone = 100000;
	medicinalMaterials = 20000000;
	ReadFacility();
	ReadElixirs();
	shop.UpdateGood(noGetLaws);
}

void USect::ReadLaws() {
	const char* path = "DataTable'/Game/DataTable/Law/Law.Law'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FLaw* temp = pDataTable->FindRow<FLaw>(i, "");
			if (temp != NULL) {
				temp->SetPrice();
				noGetLaws.Emplace(*temp);
			}
		}
	}

	for (int32 i = 0; i < 200; i++) {
		int32 random = FMath::RandRange(0, noGetLaws.Num() - 1);
		hadLaws.Emplace(noGetLaws[random]);
		noGetLaws.RemoveAt(random);
	}
		
}

void USect::ReadTreasures() {
	const char* path = "DataTable'/Game/DataTable/Treasures/Treasure.Treasure'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FTreasure* temp = pDataTable->FindRow<FTreasure>(i, "");
			if (temp != NULL)
				noGetTreasures.Emplace(*temp);
		}
	}
	int32 size = noGetTreasures.Num();
	for (int32 i = 0; i < size;i++) {
		AddTreasure(noGetTreasures[0]);
		noGetTreasures.RemoveAt(0);
	}
}

void USect::ReadFacility() {
	const char* path = "DataTable'/Game/DataTable/Facility/Facility.Facility'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FFacility* temp = pDataTable->FindRow<FFacility>(i, "");
			if (temp != NULL)
				facilities.Emplace(*temp);
		}
	}
}

void USect::ReadElixirs() {
	const char* path = "DataTable'/Game/DataTable/Elixir/Elixirs.Elixirs'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FElixirs* temp = pDataTable->FindRow<FElixirs>(i, "");
			if (temp != NULL)
				elixirs.Emplace(*temp, 2);
		}
	}
}

void USect::AddTreasure(FTreasure& t) {
	ESectValue type = t.type;
	switch (type)
	{
	case ESectValue::SpiritStone:
		ySpiritStone += t.value;
		break;
	case ESectValue::MedicinalMaterials:
		yMedicinalMaterials += t.value;
		break;
	case ESectValue::Health:
		health += t.value;
		break;
	case ESectValue::Attack:
		attack += t.value;
		break;
	case ESectValue::Defense:
		defense += t.value;
		break;
	case ESectValue::Speed:
		speed += t.value;
		break;
	default:
		break;
	}
	hadTreasure.Emplace(t);
}

TArray<int32> USect::GetFiveDisIndex() {
	TArray<int32> num;
	TArray<int32> index;
	for (int32 i = 0; i < disciples.Num(); i++)
		num.Add(i);

	for (int32 i = 0; i < 5; i++) {
		int32 random = FMath::RandRange(0, num.Num() - 1);
		index.Add(num[random]);
		num.RemoveAt(random);
	}
	return index;
}

TArray<FDisciple> USect::GetFiveDis(TArray<int32> index) {
	TArray<FDisciple> dis;
	for (int32 i = 0; i < 5; i++)
		dis.Emplace(disciples[index[i]]);
	return dis;
}

TArray<FText> USect::Explore() {
	// 獲取裝備
	int32 eNums = FMath::RandRange(0, 3);
	TArray<FEquipment> equips;
	for (int32 i = 0; i < eNums; i++) {
		FEquipment temp;
		temp.Create();
		equips.Emplace(temp);
		if (UHandleEquipment::CanAddEquipment(this, temp.type))
			UHandleEquipment::AddSingleEquipment(this, temp);
		else
			AddSpiritStone(temp.price);
	}

	// 獲取丹藥
	int32 pNums = FMath::RandRange(5, 8);
	TMap<FElixirs, int32> pills;
	for (int32 i = 0; i < pNums; i++) {
		int32 j = 0;
		int32 whichElixir = FMath::RandRange(0, 76);
		for (auto& elem : elixirs) {
			if (j == whichElixir) {
				if (elem.Value <= 1000000)
					++elem.Value;
				int32* num = pills.Find(elem.Key);
				if (num == nullptr)
					pills.Emplace(elem.Key, 1);
				else
					*num += 1;		
				break;
			}
			j++;
		}
	}

	TArray<FText> message;

	// 讀表
	const char* path = "DataTable'/Game/DataTable/Message/ExploreMessage.ExploreMessage'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : equips) {
			int32 eRow = uint8(i.type) * 7 + uint8(i.rarity);
			TArray<FStringFormatArg> arg1 = { FStringFormatArg(i.attribute.name.ToString()) };
			FReadStr* data = pDataTable->FindRow<FReadStr>(rowNames[eRow], "");
			if (data != NULL) {
				FString str = data->str;
				str = FString::Format(*str, arg1);
				message.Add(FText::FromString(*str));
			}
		}
		FReadStr* data = pDataTable->FindRow<FReadStr>(rowNames[21], "");
		if (data != NULL) {
			for (auto& elem : pills) {
				TArray<FStringFormatArg> arg2 = { FStringFormatArg(elem.Key.name.ToString()),
												  FStringFormatArg(elem.Value)};
				FString str = data->str;
				str = FString::Format(*str, arg2);
				message.Add(FText::FromString(*str));
			}
		}
	}

	return message;

}

void USect::Update() {
	Cultivate();
	FAsyncTask<SectAsyncTask>* MyTask = new FAsyncTask<SectAsyncTask>(this);
	MyTask->StartBackgroundTask();
	for (auto& i : facilities)
		i.Update();
	AddSpiritStone(ySpiritStone);
	shop.UpdateGood(noGetLaws);
	MyTask->EnsureCompletion();
}

void USect::Cultivate() {
	for (auto& i : disciples) {
		++i.year;
		i.CultivateLaw(speed);
		i.Practice();
		if (i.background == EBackground::Merchant)
			AddSpiritStone(1000);
	}
}

void USect::AddSpiritStone(int32 num) {
	if (spiritStone + num >= gCostMax)
		spiritStone = gCostMax;
	else
		spiritStone += num;
}

TMap<FElixirs, int32> USect::MakeElixirs(int32 num) {
	int32 cost = facilities[2].value - facilities[2].level * 50;
	medicinalMaterials = medicinalMaterials - cost * num;
	TMap<FElixirs, int32> made; // 煉製的丹藥
	// 丹藥機率
	TArray<int32> p = { 300, 600, 900, 1200 , 1500, 1800, 2050, 2300, 2550, 2800, 3050, 3300,
						3550, 3773, 3996 ,4196, 4396, 4596, 4796, 4996, 5183, 5343, 5503, 5663,
						5813, 5963, 6113, 6243, 6373, 6503, 6633, 6763, 6893, 7013, 7133, 7243,
						7353, 7463, 7573, 7683, 7793, 7903, 8003, 8098, 8193, 8288, 8383, 8478,
						8573, 8658, 8738, 8818, 8898, 8968, 9038, 9108, 9168, 9228, 9288, 9348,
						9408, 9468, 9502, 9536, 9570, 9600, 9630, 9655, 9680, 9700, 9720, 9740,
						9743, 9746, 9749, 9750, 10000 };
	// 讀表
	const char* path = "DataTable'/Game/DataTable/Elixir/Elixirs.Elixirs'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	// 讀得到表
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		// 煉製num顆
		for (int32 i = 0; i < num; i++) {
			// 這次機率
			int32 random = FMath::RandRange(1, 10000);
			for (int32 j = 0; j < p.Num(); j++) {
				if (random <= p[j]) {
					// 讀取丹藥資料
					FElixirs* temp = pDataTable->FindRow<FElixirs>(rowNames[j], "");
					if (temp != NULL) {
						int32* hadNums = elixirs.Find(*temp);
						if (hadNums != nullptr)
							*hadNums += 1;
						int32* make = made.Find(*temp);
						if (make == nullptr)
							made.Emplace(*temp, 1);
						else
							*make += 1;
					}
					break;
				}
			}
		}
	}

	made.KeySort([](FElixirs A, FElixirs B) {
		return A.id < B.id;
	});

	return made;
}
