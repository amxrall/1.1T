#include "stdafx.h"
#include "CustomItem.h"
#include "Model.h"
#include "ItemManager.h"
#include "Offsets.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Hook()
{
	SetCompleteHook(0xE8, 0x5D055C, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0595, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D05C6, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D05F7, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D062C, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D065D, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0697, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D06D8, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0719, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D075E, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0789, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D07B4, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D07FF, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D082C, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0858, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D089E, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D08CA, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D090F, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D090F, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0987, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D093B, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0987, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D09B2, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D09F0, &this->ShowModel);
	SetCompleteHook(0xE8, 0x5D0A1D, &this->ShowModel);
}

ModelInfo* Model::GetInfo(int Model)
{
	return (ModelInfo*)(Model * sizeof(ModelInfo) + MODEL_BASE);
}

int Model::ShowModel(int Model, int Unk1, char Unk2, int Unk3, float* Unk4, int Unk5, char Unk6)
{
	return pShowModel(Model, Unk1, Unk2, Unk3, Unk4, Unk5, Unk6);
}

void LoadItemModel(int index, char* folder, char* name) // OK
{
	if (name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = { 0 };

	wsprintf(path, "Data\\%s", folder);

	pLoadItemModel(index, path, name, -1);
}

Model gModel;