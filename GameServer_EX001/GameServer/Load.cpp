#include "StdAfx.h"
#include "LogProc.h"

void Load()
{
#if(GS_CASTLE == 0)
	QuizEvent.Load();
	DuelEvent.Load();
	PegaEvent.Load();
	SobreEvent.Load();
	BossEvent.Load();
	BloodEvent.Load();
	ChaosEvent.Load();
	DeathEvent.Load();
	TheftEvent.Load();
	CoinEvent.Load();
	RaffleEvent.Load();
	//FlagEvent.Load();
	Collector.Load();
	Bonus.Load();
	Rank.Load();
	Duel.Load();
	Quest.Load();
#endif

	Buff.Load();
	Character.Load();
	Balancer.Load();
	Setting.Load();
	Query.Load();
	HappyEvent.Load();
	Dropping.Load(); 
	News.Load();
	Command.Load();
	Reset.Load();
	Master.Load();
	Teleport.Load();
	Message.Load();
	Authority.Load();
	Bronze.Load();
	Steel.Load();
	Black.Load();
	Silver.Load();
	Golden.Load();
	Speed.Load();
	Attack.Load();
	Bank.Load();
	Potion.Load();
	Roleta.Load();
	Pick.Load();

	LogAddTD("Configurações carregadas!");
}