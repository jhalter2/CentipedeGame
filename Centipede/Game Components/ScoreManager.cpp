#include "ScoreManager.h"
#include "CmdScoreValue.h"
#include "CmdScoreByDistance.h"
#include "DisplayText.h"

ScoreManager* ScoreManager::ptrInstance = NULL;

CmdScore* ScoreManager::GetScoreCommand(ScoreEvents ev)
{
	CmdScore* pCmd = nullptr;

	switch (ev)
	{
	case ScoreEvents::FleaKilled:
		pCmd = new CmdScoreValue(FleaDeath);
		break;
	case ScoreEvents::ScorpionKilled:
		pCmd = new CmdScoreValue(ScorpionDeath);
		break;
	case ScoreEvents::MushroomKilled:
		pCmd = new CmdScoreValue(MushroomDeath);
		break;
	case ScoreEvents::MushroomPoisonKilled:
		pCmd = new CmdScoreValue(MushroomPoisonDeath);
		break;
	case ScoreEvents::MushroomRegen:
		pCmd = new CmdScoreValue(MushroomRegen);
		break;
	case ScoreEvents::SpiderKilled:
		pCmd = new CmdScoreByDistance(SpiderDistNear, SpiderDistMedium, SpiderDistFar,
			SpiderDeathNear, SpiderDeathMedium, SpiderDeathFar);
		break;
	case ScoreEvents::CentipedeBodyKilled:
		pCmd = new CmdScoreValue(CentipedeBodyDeath);
		break;
	case ScoreEvents::CentipedeHeadKilled:
		pCmd = new CmdScoreValue(CentipedeHeadDeath);
		break;
	default:
		break;
	}

	return pCmd;
}

void ScoreManager::privAddScore(int val)
{
	if (CurrentPlayerIndex != 0) {
		PlayerScores[CurrentPlayerIndex] += val;
		//tell hud to update score 
		hud->ScoreChanged(PlayerScores[CurrentPlayerIndex]);
	}
}

int ScoreManager::privGetScore(int p) {
	return PlayerScores[p];
}

void ScoreManager::SendScoreCmd(CmdScore* c)
{
	Instance().QueueCmds.push(c);
	ScoreManager::ProcessScores();
}

void ScoreManager::ProcessScores()
{
	Instance().privProcessScore();
}

void ScoreManager::privProcessScore()
{
	CmdScore* c;

	while (!QueueCmds.empty())
	{
		c = QueueCmds.front();
		c->Execute();

		QueueCmds.pop();
	}
}

void ScoreManager::privSetPlayer(int p) {
	CurrentPlayerIndex = p;
}

void ScoreManager::privSetDisplay(DisplayText* NewHud) {
	hud = NewHud;
}

DisplayText* ScoreManager::privGetDisplay() {
	return hud;
}

ScoreManager::~ScoreManager() {
	while (!QueueCmds.empty())
	{
		CmdScore* c = QueueCmds.front();
		QueueCmds.pop();
		delete c;
	}
}

void ScoreManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}