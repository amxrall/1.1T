#pragma once

#define MODEL_BASE			*(DWORD*)(0x5756AB8)
#define MODEL_SIGN			0x4064

struct ModelInfo
{
	BYTE Unknown1[0x24];	// 0
	short UnkWord24;		// 24
	short UnkWord26;		// 26
	BYTE Unknown2[0x8];		// 28
	DWORD UnkDword30;		// 30
	BYTE Unknown3[0xAC];	// 34
};

class Model
{
public:
	Model();
	~Model();

public:
	void Hook();
	ModelInfo* GetInfo(int Model);

private:
	static int ShowModel(int Model, int Unk1, char Unk2, int Unk3, float* Unk4, int Unk5, char Unk6);
};

extern Model gModel;