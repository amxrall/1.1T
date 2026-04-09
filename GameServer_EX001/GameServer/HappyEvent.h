#pragma once

struct sHappy
{
	int                     _Day;
	int                     _Hours;
	int                     _Minutes;
	int                     _Experience;
	int                     _Drop;
	int                     _Duration;
};

class cHappyEvent
{
public:
	cHappyEvent();

public:
	bool                    Load();
	void                    Run();
	void                    Finish();

public:
	bool                    _Active;
	int                     _Experience;
	int                     _Drop;
	int                     _Count;

private:
	sHappy                  HappyStruct[255];
};

extern cHappyEvent HappyEvent;