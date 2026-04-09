#pragma once

#define TEXTURE_MAX				0x488E
#define TextureMax				*(DWORD*)(0x7D16FE8)
#define TextureLoad  			((void(*)(int, char*, char*, int)) 0x5FACA0)
#define TextureCall  			((void(*)(int, char*, int, int, int)) 0x5FA860)

struct sTexture
{
	char Name[32];
	float Width;			// 20
	float Height;			// 24
	DWORD UnkDword28;		// 28
	GLuint Texture;			// 2C
	BYTE UnkByte30;			// 30
	BYTE Unknown3[0x03];	// 31
	BYTE* UnkPByte34;		// 34
};

class cTexture
{
public:
	void Load();
	static void gObjTexture();

private:
	char _Buffer[255];

private:
	sTexture Textures[TEXTURE_MAX];
};

extern cTexture Texture;