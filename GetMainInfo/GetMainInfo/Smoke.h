#pragma once

#define MAX_SMOKE 255

struct SMOKE_EFFECT
{
	WORD			    _Index;
	int                 _Item;
	int			        _Count;
	float               _ColorR;
	float               _ColorG;
	float               _ColorB;
};
struct sSmoke
{
	WORD			    _Index;
	float			    _ColorR;
	float			    _ColorG;
	float			    _ColorB;
};

class cSmoke
{
public:
	cSmoke();
	virtual ~cSmoke();
	void Init();
	void SetInfo(SMOKE_EFFECT info);
	// ----
	bool Load(const char* path);
	int Get(DWORD Type);
	static void Effect();
public :
	SMOKE_EFFECT m_Smoke[MAX_SMOKE];
private:
	sSmoke			    SmokeStruct[255];
};

extern cSmoke Smoke;