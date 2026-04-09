#include "StdAfx.h"


bool cSetting::Load()
{	
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Config\\Config.txt"), Group);
	if (Group.GetSection(1, Section))
	{
		this->_Checksum = Section.Rows[0].GetInt(0);
		this->_Points[0] = Section.Rows[0].GetInt(1);
		this->_Points[1] = Section.Rows[0].GetInt(2);
		this->_Points[2] = Section.Rows[0].GetInt(3);

		this->_Personal = Section.Rows[1].GetInt(0);
		this->_MaxStatus = Section.Rows[1].GetInt(1);
		this->_Reset = Section.Rows[1].GetInt(2);
		this->_Time = Section.Rows[1].GetInt(3);

		this->_Party[0] = Section.Rows[2].GetInt(0);
		this->_Party[1] = Section.Rows[2].GetInt(1);
		this->_Party[2] = Section.Rows[2].GetInt(2);
		this->_Party[3] = Section.Rows[2].GetInt(3);

		this->_Party[4] = Section.Rows[3].GetInt(0);
		this->_Party[5] = Section.Rows[3].GetInt(1);
		this->_Party[6] = Section.Rows[3].GetInt(2);
		this->_Type = Section.Rows[3].GetInt(3);

		this->_Jewel1[0] = Section.Rows[4].GetInt(0);
		this->_Jewel1[1] = Section.Rows[4].GetInt(1);
		this->_Jewel1[2] = Section.Rows[4].GetInt(2);
		this->_Jewel1[3] = Section.Rows[4].GetInt(3);

		this->_Jewel2[0] = Section.Rows[5].GetInt(0);
		this->_Jewel2[1] = Section.Rows[5].GetInt(1);
		this->_Jewel2[2] = Section.Rows[5].GetInt(2);
		this->_Jewel2[3] = Section.Rows[5].GetInt(3);

		this->_Jewel3[0] = Section.Rows[6].GetInt(0);
		this->_Jewel3[1] = Section.Rows[6].GetInt(1);
		this->_Jewel3[2] = Section.Rows[6].GetInt(2);
		this->_Jewel3[3] = Section.Rows[6].GetInt(3);

		this->_Mix1[0] = Section.Rows[7].GetInt(0);
		this->_Mix1[1] = Section.Rows[7].GetInt(1);
		this->_Mix1[2] = Section.Rows[7].GetInt(2);
		this->_Mix1[3] = Section.Rows[7].GetInt(3);

		this->_Mix2[0] = Section.Rows[8].GetInt(0);
		this->_Mix2[1] = Section.Rows[8].GetInt(1);
		this->_Mix2[2] = Section.Rows[8].GetInt(2);
		this->_Mix2[3] = Section.Rows[8].GetInt(3);

		this->_Mix3[0] = Section.Rows[9].GetInt(0);
		this->_Mix3[1] = Section.Rows[9].GetInt(1);
		this->_Mix3[2] = Section.Rows[9].GetInt(2);
		this->_Mix3[3] = Section.Rows[9].GetInt(3);

		this->_Mix4[0] = Section.Rows[10].GetInt(0);
		this->_Mix4[1] = Section.Rows[10].GetInt(1);
		this->_Mix4[2] = Section.Rows[10].GetInt(2);
		this->_Mix4[3] = Section.Rows[10].GetInt(3);

		this->_Mix5[0] = Section.Rows[11].GetInt(0);
		this->_Mix5[1] = Section.Rows[11].GetInt(1);
		this->_Mix5[2] = Section.Rows[11].GetInt(2);
		this->_Mix5[3] = Section.Rows[11].GetInt(3);
		// -----
#if(GS_CASTLE == 0)
		this->_Experience[0] = Section.Rows[12].GetInt(0);
		this->_Experience[1] = Section.Rows[12].GetInt(1);
		this->_Experience[2] = Section.Rows[12].GetInt(2);
		this->_Experience[3] = Section.Rows[12].GetInt(3);
#endif
	}
	this->_Character = GetPrivateProfileInt("SERVER", "Character", 0, ".\\Data\\Config\\Config.txt");
	this->_PetAngel = GetPrivateProfileInt("SERVER", "Angel_Imortal", 0, ".\\Data\\Config\\Config.txt");
	this->_PetImp = GetPrivateProfileInt("SERVER", "Imp_Imortal", 0, ".\\Data\\Config\\Config.txt");
	this->_PetUniria = GetPrivateProfileInt("SERVER", "Uniria_Imortal", 0, ".\\Data\\Config\\Config.txt");
	this->_PetDinorant = GetPrivateProfileInt("SERVER", "Dinorant_Imortal", 0, ".\\Data\\Config\\Config.txt");
	this->_NewPets = GetPrivateProfileInt("SERVER", "NewPets_Imortal", 0, ".\\Data\\Config\\Config.txt");
	return true;

}

cSetting Setting;