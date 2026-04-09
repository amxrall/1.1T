#include "StdAfx.h"

cManager::cManager(void)
{
}

cManager::~cManager(void)
{
}

bool cManager::Initialize()
{
	if (!this->Database())
	{
		return false;
	}

	return true;
}

bool cManager::Database()
{
	bool Return = false;

	Manager.Load();

	if (this->Connect(this->_Host, this->_Data, this->_User, this->_Senha) == true)
	{
		Return = true;
	}
	else
	{
		MessageBox(NULL, "Conexão com SQL Server falhou!\n Por favor verifique o arquivo 'Config.txt", "GBTeam Emulador", MB_OK | MB_ICONERROR);
		ExitProcess(0);

		this->DiagnosticConn();
	}

	return Return;
}

bool cManager::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Config\\Config.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		strcpy_s(&this->_User[0], sizeof(this->_User), (Section.Rows[0].GetStringPtr(0)));
		strcpy_s(&this->_Senha[0], sizeof(this->_Senha), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(&this->_Data[0], sizeof(this->_Data), (Section.Rows[0].GetStringPtr(2)));
		strcpy_s(&this->_Host[0], sizeof(this->_Host), (Section.Rows[0].GetStringPtr(3)));
	}

	return true;
}

void cManager::OnError(const char * Message, ...)
{
	this->Log((char*)Message);
}

void cManager::OnMessage(const char * Message, ...)
{
	this->Log((char*)Message);
}

void cManager::OnQuery(const char * Message, ...)
{
	this->Log((char*)Message);
}

int cManager::VipCount(char* Account)
{
	this->ExecFormat("SELECT Vip FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	int Vip = this->GetInt("Vip");

	this->Clear();

	return Vip;
}

int cManager::ResetCount(char* Character)
{
	this->ExecFormat("SELECT Resets from Character WHERE Name = '%s'", Character);

	this->Fetch();

	int Reset = this->GetInt("Resets");

	this->Clear();

	return Reset;
}

int cManager::MasterCount(char* Character)
{
	this->ExecFormat("SELECT MResets from Character WHERE Name = '%s'", Character);

	this->Fetch();

	int Master = this->GetInt("MResets");

	this->Clear();

	return Master;
}

int cManager::CheckVault(char* Account)
{
	this->ExecFormat("SELECT VaultID FROM warehouse WHERE AccountID = '%s'", Account);

	this->Fetch();

	int Vault = this->GetInt("VaultID");

	this->Clear();

	return Vault;
}

int cManager::MoneyGold(char* Account)
{
	int Gold;
	// 
	this->ExecFormat("SELECT Gold FROM MuOnline.dbo.MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	Gold = this->GetInt("Gold");

	this->Clear();

	return Gold;
}

int cManager::MoneyCash(char* Account)
{
	int Cash;

	this->ExecFormat("SELECT Cash FROM MuOnline.dbo.MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	Cash = this->GetInt("Cash");

	this->Clear();

	return Cash;
}

bool cManager::JewelsCount(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT Bless,Soul, Life, Chaos, Creation, Guardian FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	gObj[aIndex].Custom->Jewels[Bank.Bless] = this->GetInt("Bless");
	gObj[aIndex].Custom->Jewels[Bank.Soul] = this->GetInt("Soul");
	gObj[aIndex].Custom->Jewels[Bank.Life] = this->GetInt("Life");
	gObj[aIndex].Custom->Jewels[Bank.Chaos] = this->GetInt("Chaos");
	gObj[aIndex].Custom->Jewels[Bank.Creation] = this->GetInt("Creation");
	gObj[aIndex].Custom->Jewels[Bank.Guardian] = this->GetInt("Guardian");

	this->Clear();

	return Select;
}

bool cManager::CheckBonus(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT Bonus FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	gObj[aIndex].Custom->Bonus = this->GetInt("Bonus");

	this->Clear();

	return Select;
}

/*bool cManager::CoinCount(int aIndex, char* Account)
{
	gObj[aIndex].Custom->m_Cash = this->ExecFormat("Cash", "SELECT Cash FROM MEMB_INFO WHERE memb___id = '%s'", gObj[aIndex].AccountID);
	// ---
	gObj[aIndex].Custom->m_Gold = this->ExecFormat("Gold", "SELECT Gold FROM MEMB_INFO WHERE memb___id = '%s'", gObj[aIndex].AccountID);
	bool Select = this->ExecFormat("SELECT %s, %s,Gold,Cash, FROM MEMB_INFO WHERE memb___id = '%s'", Roleta._Column, Duel._Column,Account);

	this->Fetch();

	gObj[aIndex].Custom->Coin[0] = this->GetInt(Roleta._Column);
	gObj[aIndex].Custom->Coin[1] = this->GetInt(Duel._Column);
	

	gObj[aIndex].Custom->m_Gold = this->GetInt("Gold");
	gObj[aIndex].Custom->m_Cash = this->GetInt("Cash");
	gObj[aIndex].Custom->Coin[4] = this->GetInt("Amount");

	this->Clear();

	return Select;
}*/

bool cManager::QuestCount(int aIndex, char* Character)
{
	bool Select = this->ExecFormat("SELECT Number, Start, Kills FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	Quest.PlayerStruct[aIndex]._Index = this->GetInt("Number");
	Quest.PlayerStruct[aIndex]._Start = this->GetInt("Start");
	Quest.PlayerStruct[aIndex]._Kills = this->GetInt("Kills");

	this->Clear();

	return Select;
}

void cManager::Log(char * Text)
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE * stream;

	TCHAR String[512];

	wsprintf(String, "SQL_LOG\\%02d-%02d-%02d_SQL.txt", t.wYear, t.wMonth, t.wDay);

	stream = fopen(String, "a+");

	fprintf(stream, "%02d:%02d:%02d - %s\n", t.wHour, t.wMinute, t.wSecond, Text);

	fclose(stream);
}

cManager Manager = cManager();