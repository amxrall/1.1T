#pragma once

class cCollector
{
public:
	cCollector();

public:
	bool Load();

public:
	bool				_Active;
	int                 _Section;
	int				    _Type[5];
	int				    _Index[5];
	int				    _Level[5];
	int				    _Quantity[5];
	int                 _Value[5];
	char                _Name[5][60];
	char                _Coin[5][60];
	char				m_Gold[60];
	char				m_Cash[60];
	char                _Buffer[60];
};

extern cCollector Collector;