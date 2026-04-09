#pragma once

class cManager : public cDataBase
{
public:
	cManager(void);
	~cManager(void);

public:
	bool Initialize();
	bool Database();
	bool Load();
	void OnMessage(const char * Message, ...);
	void OnError(const char * Message, ...);
	void OnQuery(const char * Message, ...);
	int VipCount(char* Account);
	int ResetCount(char* Character);
	int MasterCount(char* Character);
	int CheckVault(char* Account);
	int MoneyGold(char* Account);
	int MoneyCash(char* Account);
	bool JewelsCount(int aIndex, char* Account);
	bool CheckBonus(int aIndex, char* Account);
	//bool CoinCount(int aIndex, char* Account);
	bool QuestCount(int aIndex, char* Character);
	void Log(char * Text);

private:
	char _Host[50];
	char _Data[50];
	char _User[50];
	char _Senha[50];
};

extern cManager Manager;