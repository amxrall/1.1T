#pragma once

class cSetting
{
public:
	bool Load();

public:
	int					_Checksum;
	int					_Points[3];
	int					_Personal;
	int					_MaxStatus;
	int                 _Reset;
	int                 _Time;
	int                 _Party[7];
	int                 _Type;
	int                 _Jewel1[4];
	int                 _Jewel2[4];
	int                 _Jewel3[4];
	int                 _Mix1[4];
	int                 _Mix2[4];
	int                 _Mix3[4];
	int                 _Mix4[4];
	int                 _Mix5[4];
	int			        _Experience[4];
	char                _Serial[24];
	int                 _Character;
	int					_Pets;
	int					_PetAngel;
	int					_PetImp;
	int					_PetUniria;
	int					_PetDinorant;
	int					_NewPets;
	char				 m_CustomerName[32];
	char				 m_CustomerHardwareId[36];
};

extern cSetting Setting;