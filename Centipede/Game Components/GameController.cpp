#include "GameController.h"
//#include "HUD.h"
//#include "FinalScore.h"

GameController* GameController::ptrInstance;

GameController::GameController()
{
	ResetScore();
}

void GameController::ResetScore()
{
	Score = 0;
}

void GameController::AddScore(int v)
{
	Score += v;
	//HUD::ScoreUpdate(Score);
}

int GameController::GetScore()
{
	return Score;
}

void GameController::PlayerDies()
{
	//new FinalScore();
}


void GameController::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}