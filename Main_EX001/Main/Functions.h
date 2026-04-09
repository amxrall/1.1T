#pragma once

enum ASM
{
	JMP = 0xE9,
	JE = 0x74,
	JNE = 0x75,
	JGE = 0x7D,
	NOP = 0x90,
	CALL = 0xE8,
	EAX = 0x50,
};
void SetWord(DWORD offset, WORD value);
void Hook(BYTE Head, DWORD Offset, ...);
void HookJump(DWORD Offset, LPVOID Function);
void SetCompleteHook(BYTE head, DWORD offset, ...);
void SetDword(DWORD offset, DWORD value);
void HookCall(DWORD Offset, LPVOID Function);
void SetNop(DWORD Offset, int Size);
void MemorySet(DWORD offset, DWORD value, DWORD size);
void SetByte(DWORD offset, BYTE value);
DWORD SetFloat(const LPVOID Offset, float Value);
DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd);
DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue);
DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetByte(const LPVOID dwOffset, const BYTE btValue);
int Registry(const char* Section);

void VirtualizeOffset(DWORD offset, DWORD size);

void PacketArgumentEncrypt(char* out_buff, char* in_buff, int size);

char* ConvertModuleFileName(char* name);

bool FileExists(char* name);

int GetTextPosX(char* buff, int PosX);

int GetTextPosY(char* buff, int PosY);

float ImgCenterScreenPosX(float Size);

float ImgCenterScreenPosY(float Size);