#include "StdAfx.h"

void Hook(BYTE Head, DWORD Offset, ...)
{
	if (Head != 0xFF)
	{
		*(BYTE*)(Offset) = Head;
	}

	DWORD* Function = &Offset + 1;
	*(DWORD*)(Offset + 1) = (*Function) - (Offset + 5);
}
void SetWord(DWORD offset, WORD value)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 2, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset, 2, OldProtect, &OldProtect);
}

void SetByte(DWORD offset, BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 1, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset, 1, OldProtect, &OldProtect);
}

void SetCompleteHook(BYTE head, DWORD offset, ...)
{
	DWORD OldProtect;
	VirtualProtect((void*)offset, 5, PAGE_EXECUTE_READWRITE, &OldProtect);

	if (head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset + 1;
	*(DWORD*)(offset + 1) = (*function) - (offset + 5);

	VirtualProtect((void*)offset, 5, OldProtect, &OldProtect);
};

DWORD SetByte(const LPVOID dwOffset, const BYTE btValue)
{
	return WriteMemory(dwOffset, (LPVOID)&btValue, sizeof(BYTE));
}

void SetDword(DWORD offset, DWORD value)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 4, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset, 4, OldProtect, &OldProtect);
}

void MemorySet(DWORD offset, DWORD value, DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, size, PAGE_EXECUTE_READWRITE, &OldProtect);

	memset((void*)offset, value, size);

	VirtualProtect((void*)offset, size, OldProtect, &OldProtect);
}
void HookJump(DWORD Offset, LPVOID Function)
{
	*(BYTE*)(Offset) = 0xE9;
	*(DWORD*)(Offset + 1) = (DWORD)Function - (Offset + 5);
}

void HookCall(DWORD Offset, LPVOID Function)
{
	*(BYTE*)(Offset) = 0xE8;
	*(DWORD*)(Offset + 1) = (DWORD)Function - (Offset + 5);
}

void SetNop(DWORD Offset, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		*(BYTE*)(Offset + i) = 0x90;
	}
}

DWORD SetFloat(const LPVOID Offset, float Value)
{
	return *(float*)(Offset, &Value, sizeof(float));
}

DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf = new BYTE[wCount];
	// ---
	memset(lpBuf, btValue, wCount);
	// ---
	return WriteMemory(dwAddress, (LPVOID)lpBuf, wCount);
}

DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ---
	btBuf[0] = 0xE9;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode = 0;
	DWORD dwOldProtect = 0;
	// ---
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	// ---
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ---
	memcpy(lpAddress, lpBuf, uSize);
	// ---
	DWORD dwBytes = 0;
	// ---
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBytes);
	// ---
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ---
	return 0x00;
}

DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ---
	btBuf[0] = cmd;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwMyFuncOffset - ((ULONG_PTR)dwJmpOffset + 5);
	// ---
	btBuf[0] = cmd;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwJmpOffset, (LPVOID)btBuf, sizeof(btBuf));
}

int Registry(const char* Section)
{
	HKEY Key;

	int Value = 0;

	DWORD Size = sizeof(int);

	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Webzen\\MU\\Config", &Key) == 0)
	{
		if (RegQueryValueEx(Key, Section, nullptr, nullptr, (LPBYTE)(&Value), &Size) == 0)
		{
			return Value;
		}

		RegCloseKey(Key);
	}

	return FALSE;
}
void VirtualizeOffset(DWORD offset, DWORD size)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, size, PAGE_EXECUTE_READWRITE, &OldProtect);

	DWORD HookAddr = (DWORD)malloc(size + 5);

	memcpy((void*)HookAddr, (void*)offset, size);

	*(BYTE*)(HookAddr + size) = 0xE9;

	*(DWORD*)(HookAddr + size + 1) = (offset + size) - ((HookAddr + size) + 5);

	*(BYTE*)(offset) = 0xE9;

	*(DWORD*)(offset + 1) = HookAddr - (offset + 5);

	memset((void*)(offset + 5), 0x90, (size - 5));

	VirtualProtect((void*)offset, size, OldProtect, &OldProtect);
}

void PacketArgumentEncrypt(char* out_buff, char* in_buff, int size)
{
	BYTE XorTable[3] = { 0xFC, 0xCF, 0xAB };

	for (int n = 0; n < size; n++)
	{
		out_buff[n] = in_buff[n] ^ XorTable[n % 3];
	}
}

char* ConvertModuleFileName(char* name)
{
	static char buff[MAX_PATH] = { 0 };

	for (int n = strlen(name); n > 0; n--)
	{
		if (name[n] == '\\')
		{
			strcpy_s(buff, sizeof(buff), &name[(n + 1)]);

			break;
		}
	}

	return buff;
}

bool FileExists(char* name)
{
	if (CreateFile(name, 0, 0, 0, OPEN_EXISTING, 0, 0) == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	return true;
};

int GetTextPosX(char* buff, int PosX)
{
	HDC hdc = GetDC(pGameWindow);

	SIZE sz;

	GetTextExtentPoint(hdc, buff, strlen(buff), &sz);

	return (PosX - (640 * sz.cx / *(DWORD*)MAIN_RESOLUTION_X >> 1));
}

int GetTextPosY(char* buff, int PosY)
{
	HDC hdc = GetDC(pGameWindow);

	SIZE sz;

	GetTextExtentPoint(hdc, buff, strlen(buff), &sz);

	return (PosY - (480 * sz.cy / *(DWORD*)MAIN_RESOLUTION_Y >> 1));
}

float ImgCenterScreenPosX(float Size)
{
	return (320.0f - (Size / 2.0f));
}

float ImgCenterScreenPosY(float Size)
{
	return (216.0f - (Size / 2.0f));
}