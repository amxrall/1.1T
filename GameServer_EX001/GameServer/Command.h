#pragma once

class Commands
{
public:
	bool Load();
	bool Management(PMSG_CHATDATA* lpMsg, int aIndex);
	void Post(int aIndex, char* msg);
	void Add(int aIndex, char* msg, int Status);
	void ReAdd(int aIndex);
	void Clear(int aIndex);
	void Ware(int aIndex, char* msg);
	void Money(int aIndex);
	void Online(int aIndex);
	void Premiar(int aIndex, char* msg);
	void MoveAll(int aIndex, char* msg);
	void Skin(int aIndex, char* msg);
	void Move(int aIndex, char* msg);
	void FireWork(int aIndex);
	void Drop(int aIndex, char* msg);
	void Evento(int aIndex, char* msg);
	void Ir(int aIndex);
	static void Thread(void * lpParam);
	void Hide(int aIndex, char* msg);
	void Full(int aIndex);

public:
	bool					_Active[15];
	bool                    _Event;
	int					    _VipCount[2];
	int					    _Level[6];
	int					    _Zen[7];
	int					    _Color;
	int                     _Comando;
	int					    _Ware[4];
	int                     _Number;
	int                     _MapNumber;
	int                     _X;
	int                     _Y;
	int                     _Count;
	DWORD		            _Delay;
	char					_Formato[50];
	char					_Syntax[20][25];
	char                    _Name[255];
	char                    _Notice[255];
	char                    _Buffer[255];
};

extern Commands Command;