#include "StdAfx.h"
#include "DSProtocol.h"

bool cBank::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Bank.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Level = Section.Rows[0].GetInt(1);
		this->_Zen = Section.Rows[0].GetInt(2);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(3)));
	}

	return true;
}

void cBank::Command(int aIndex, char* msg)
{
	if (!this->_Active)
	{
		Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (gObj[aIndex].Level < this->_Level)
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen)
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen);
		return;
	}
	else if (gObj[aIndex].m_IfState.use != 0)
	{
		Function.MsgOutput(aIndex, 1, "Feche todas as janelas para usar o banco.");
		return;
	}

	this->_Jewel[0] = 0, this->_Trans[0] = 0;

	sscanf(msg, "%s %s %d", &this->_Trans, &this->_Jewel, &this->_Count);

	if (strlen(msg) < 3 || this->_Trans[0] == 0 || strcmpi(this->_Trans, "deposito") && strcmpi(this->_Trans, "saque") && strcmpi(this->_Trans, "saldo"))
	{
		Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Function.MsgOutput(aIndex, 1, "Digite: %s saldo ou deposito/saque.", this->_Syntax);
		return;
	}

	if (!strcmpi(this->_Trans, "saldo"))
	{
		Function.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d Bless(s)", gObj[aIndex].Custom->Jewels[this->Bless]);
		Function.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d Soul(s)", gObj[aIndex].Custom->Jewels[this->Soul]);
		Function.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d Life(s)", gObj[aIndex].Custom->Jewels[this->Life]);
		Function.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d Chaos(s)", gObj[aIndex].Custom->Jewels[this->Chaos]);
		Function.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d Creation(s)", gObj[aIndex].Custom->Jewels[this->Creation]);
		Function.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d Guardian(s)", gObj[aIndex].Custom->Jewels[this->Guardian]);
		return;
	}

	if (this->_Jewel[0] == 0 || strcmpi(this->_Jewel, "bless") && strcmpi(this->_Jewel, "soul") && strcmpi(this->_Jewel, "life") && strcmpi(this->_Jewel, "chaos") && strcmpi(this->_Jewel, "creation") && strcmpi(this->_Jewel, "guardian"))
	{
		Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Function.MsgOutput(aIndex, 1, "Digite: %s deposito/saque joia quantidade.", this->_Syntax);
		return;
	}

	int Item = !strcmpi(this->_Jewel, "bless") ? ITEMGET(14, 13) : !strcmpi(this->_Jewel, "soul") ? ITEMGET(14, 14) : !strcmpi(this->_Jewel, "life") ? ITEMGET(14, 16) : !strcmpi(this->_Jewel, "chaos") ? ITEMGET(12, 15) : !strcmpi(this->_Jewel, "creation") ? ITEMGET(14, 22) : !strcmpi(this->_Jewel, "guardian") ? ITEMGET(14, 31) : -1;

	int Jewel = !strcmpi(this->_Jewel, "bless") ? this->Bless : !strcmpi(this->_Jewel, "soul") ? this->Soul : !strcmpi(this->_Jewel, "life") ? this->Life : !strcmpi(this->_Jewel, "chaos") ? this->Chaos : !strcmpi(this->_Jewel, "creation") ? this->Creation : !strcmpi(this->_Jewel, "guardian") ? this->Guardian : -1;

	if (!strcmpi(this->_Trans, "deposito"))
	{
		int Total = Function.CheckInventory(aIndex, Item, 0);

		if (this->_Count <= 0)
		{
			Function.MsgOutput(aIndex, 1, "É preciso digitar o valor do depósito.");
			return;
		}
		else if (this->_Count > Total)
		{
			Function.MsgOutput(aIndex, 1, "Você só tem %d %s(s)", Total, this->_Jewel);
			return;
		}

		if (Total != 0)
		{
			Function.DeleteInventory(aIndex, Item, 0, this->_Count);

			gObj[aIndex].Custom->Jewels[Jewel] += this->_Count;

			char * Coluna = Jewel == this->Bless ? "Bless" : Jewel == this->Soul ? "Soul" : Jewel == this->Life ? "Life" : Jewel == this->Chaos ? "Chaos" : Jewel == this->Creation ? "Creation" : Jewel == this->Guardian ? "Guardian" : "null";

			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %d WHERE memb___id = '%s'", Coluna, gObj[aIndex].Custom->Jewels[Jewel], gObj[aIndex].AccountID);

			Function.MsgOutput(aIndex, 1, "Deposito de %d %s(s) efetuado!", this->_Count, this->_Jewel);
			Function.MsgOutput(aIndex, 1, "Saldo atual de %d %s(s)", gObj[aIndex].Custom->Jewels[Jewel], this->_Jewel);
		}

	}
	else if (!strcmpi(this->_Trans, "saque"))
	{
		if (this->_Count <= 0)
		{
			Function.MsgOutput(aIndex, 1, "É preciso digitar o valor do saque.");
			return;
		}
		else if (this->_Count > gObj[aIndex].Custom->Jewels[Jewel])
		{
			Function.MsgOutput(aIndex, 1, "Você só tem %d %s(s)", gObj[aIndex].Custom->Jewels[Jewel], this->_Jewel);
			return;
		}

		if (!Function.InventoryFullCheck(aIndex, Item))
		{
			Function.MsgOutput(aIndex, 1, "O inventário está cheio!");
			return;
		}

		int Check = Function.InventoryFullCheck(aIndex, Item);

		if (this->_Count > Check)
		{
			this->_Count = Check;
		}

		for (int i = 0; i < this->_Count; i++)
		{
			ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, 0, 0, 0, 0, 0, aIndex, 0, 0);

			gObj[aIndex].Custom->Jewels[Jewel]--;
		}

		if (gObj[aIndex].Custom->Jewels[Jewel] < 0)
		{
			gObj[aIndex].Custom->Jewels[Jewel] = 0;
		}

		char * Coluna = Jewel == this->Bless ? "Bless" : Jewel == this->Soul ? "Soul" : Jewel == this->Life ? "Life" : Jewel == this->Chaos ? "Chaos" : Jewel == this->Creation ? "Creation" : Jewel == this->Guardian ? "Guardian" : "null";

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %d WHERE memb___id = '%s'", Coluna, gObj[aIndex].Custom->Jewels[Jewel], gObj[aIndex].AccountID);

		Function.MsgOutput(aIndex, 1, "Saque de %d %s(s) efetuado!", this->_Count, this->_Jewel);
		Function.MsgOutput(aIndex, 1, "Saldo restante de %d %s(s)", gObj[aIndex].Custom->Jewels[Jewel], this->_Jewel);
	}
}

cBank Bank;