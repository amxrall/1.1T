#pragma once

class cFunctions
{
public:
	void MsgOutput(int aIndex, int Type, char* Msg, ...);
	void AllServerAnnounce(char* message, ...);
	void SendMapServerGroupMsg(char* message);
	void UpdateCharacter(int aIndex, bool Effect);
	int GetPlayerIndex(char* Name);
	int MonsterAdd(int MobID, int MapID, int CoordX, int CoordY);
	void SendLevelUp(int aIndex);
	void SendMain(int aIndex);
	void Blue(LPCSTR Nome, LPSTR Mensagem, int aIndex);
	void Green(LPCSTR Nome, LPSTR Mensagem, int aIndex);
	void Yellow(LPCSTR Nome, LPSTR Mensagem, int aIndex);
	void Golden(int aIndex, const char* Format, ...);
	bool CheckItem(int aIndex);
	float GetStatus(int aIndex, BYTE Class, BYTE Type);
	void FireWork(int aIndex);
	void PlayerOut(LPOBJ lpObj);
	int CheckInventory(int aIndex, int Type, int Level);
	int DeleteInventory(int aIndex, int Type, int Level, int Quantity);
	int InventoryFullCheck(int aIndex, short Item);
	void HealthBarSend(LPOBJ lpObj);
	void UseItem(PMSG_USEITEM* lpMsg, int aIndex);
	int Rand(int Min, int Max);
	void UpdateRank(int aIndex);
	BYTE gObjInventoryInsertItemEx(int aIndex, CItem Item);
	BOOL Position(int aIndex, int MapNumber, int X, int Y, int View);
	static void Thread(void* lpParam);
};

extern cFunctions Function;
