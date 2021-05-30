// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

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

static int32 PrintLog(NS_SLUA::lua_State* L) {
	FString str;
	size_t len;
	const char* s = luaL_tolstring(L, 1, &len);
	if (s) str += UTF8_TO_TCHAR(s);
	NS_SLUA::Log::Log("PrintLog %s", TCHAR_TO_UTF8(*str));
	return 0;
}

UMyGameInstance::UMyGameInstance() : state("main", this) {
	/*
	disciples.SetNum(10);
	cultivationLaw = NewObject<UCultivationLaw>(this, TEXT("CultivationLaw"));
	cultivationLaws.SetNum(2);
	FString objectName = "cultivationLaws";
	for (int i = 0; i < cultivationLaws.Num(); i++) {
		FString temp = objectName;
		temp.AppendInt(i + 1);
		cultivationLaws[i] = NewObject<UCultivationLaw>(this, FName(*temp));
	}
	cultivationLaws[1] = cultivationLaw;
	cultivationLaw = NULL;
	cultivationLaws.RemoveAt(1);
	*/
	sect = NewObject<USect>(this, TEXT("sect"));
	CreateEnemys();
}

void UMyGameInstance::Init() {
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

void UMyGameInstance::LuaStateInitCallback() {
	NS_SLUA::lua_State* L = state.getLuaState();
	lua_pushcfunction(L, PrintLog);
	lua_setglobal(L, "PrintLog");
}

void UMyGameInstance::CreateEnemys() {
	FCommonAttribute temp;
	temp.SetName("AAAA");
	temp.SetAttack(10000);
	temp.SetHealth(10000);
	temp.SetDefense(10000);
	for (int32 i = 0; i < 10; i++)
		enemys.Emplace(temp);
}

USect* UMyGameInstance::GetSect() {
	return sect;
}

TArray<FCommonAttribute> UMyGameInstance::GetEnemys() {
	return enemys;
}

void UMyGameInstance::SetEnemyIndex(int32 index) {
	enemyIndex = index;
}

int32 UMyGameInstance::GetEnemyIndex() {
	return enemyIndex;
}
