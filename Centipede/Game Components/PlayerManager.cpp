#include "PlayerManager.h"
#include "Ship.h"
#include "TEAL\CommonElements.h"
#include "ShipController.h"
#include "Bullet.h"
#include "LevelController.h"
#include "ShipFactory.h"
#include "DisplayText.h"
#include "ScoreManager.h"
#include "MushroomField.h"
#include "CritterSpawner.h"

PlayerManager* PlayerManager::ptrInstance = NULL;

PlayerManager::PlayerManager() {
	CP = 0;
	PlayerCount = 0;
	TwoPlayer = false;
	TwoPlayerDied = false;
}

void PlayerManager::privPlayerDied() {
	PlayerLives[CP]--;
	if (PlayerLives[CP] == 0 && TwoPlayer == false) OnePlayerGameOver();
	else if (PlayerLives[0] == 0 && PlayerLives[1] != 0 && TwoPlayer == true) TwoPlayerP1Died();
	else if (PlayerLives[0] == 0 && PlayerLives[1] == 0 && TwoPlayer == true) TwoPlayerGameOver();
	else if (TwoPlayer == true) TwoPlayerSwitch();
	else {
		dt->RemoveP1Lives();
		CritterSpawner::ClearField();
		pM->RegenShrooms();
		SetAlarm(4, respawn_delay);
	}
}

void PlayerManager::OnePlayerGameOver() {
	pM->RegenShrooms();
	if (dt->IsNewHighScore()) {
		CritterSpawner::ClearField();
		dt->GameOver();
		SetAlarm(3, text_display);

	}
	else {
		dt->GameOver();
		CritterSpawner::ClearField();
		SetAlarm(1, text_display);
	}
}

void PlayerManager::TwoPlayerSwitch() {
	pM->ChangePlayer();
	pM->RegenShrooms();
	CritterSpawner::ChangeCurrentPlayer();
	CritterSpawner::CancelAlarms();
	CritterSpawner::ClearExtraCritters();
	if (CP == 0) {
		dt->RemoveP1Lives();
		CP = 1;
		dt->NextPlayer();
	}
	else {
		dt->RemoveP2Lives();
		CP = 0;
		dt->NextPlayer();
	}
	SetAlarm(2, text_display);
}

void PlayerManager::TwoPlayerP1Died() {
	TwoPlayerSwitch();
}

void PlayerManager::TwoPlayerGameOver() {
	OnePlayerGameOver();
}

void PlayerManager::privRegisterPlayer(Ship* sp) {
	CurrentPlayer = sp;
	players[PlayerCount] = sp;
	PlayerCount++;
}

void PlayerManager::privSetActivePlayer(int p) {
	//for two player
	CurrentPlayer = players[p];
	PlayerController->ChangePlayer(CurrentPlayer);
}

void PlayerManager::privSetPlayerController(ShipController* pc) {
	PlayerController = pc;
}

Ship* PlayerManager::privGetCurrentPlayer() {
	return CurrentPlayer;
}

void PlayerManager::privActivateTwoPlayer() {
	TwoPlayer = true;
}

void PlayerManager::privDeactivateTwoPlayer() {
	TwoPlayer = false;
}

void PlayerManager::privSetLevelControl(LevelController* lc) {
	LevelControl = lc;
}

void PlayerManager::privSetMushroomField(MushroomField* mf) {
	pM = mf;
}

void PlayerManager::privSetDisplayText(DisplayText* pDt) {
	dt = pDt;
}

//time to show "game over" text
void PlayerManager::Alarm1() {
	LevelControl->LoadAttractorScene();
}

//time to show "player x" text during 2p mode player switch
void PlayerManager::Alarm2() {
	dt->RemovePlayerText();
	if (CP == 0) CritterSpawner::LoadCurrentWaveInfo();
	else CritterSpawner::LoadP2WaveInfo();
	SetAlarm(4, 0.0f);
}

//time to switch into attractor with entering initials
void PlayerManager::Alarm3() {
	LevelControl->LoadAttractorHSScene();
}

//respawn player while lives > 0
void PlayerManager::Alarm4() {
	Ship* sp = ShipFactory::CreateShip(pM);
	CurrentPlayer = sp;
	PlayerController->ChangePlayer(CurrentPlayer);
}

void PlayerManager::Terminate() {
	//delete ptrInstance;
	ptrInstance = nullptr;
}