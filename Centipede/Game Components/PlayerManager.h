#ifndef _PlayerManager
#define _PlayerManager

#include "TEAL\CommonElements.h"

class Ship;
class ShipController;
class Bullet;
class LevelController;
class MushroomField;
class DisplayText;

class PlayerManager : public GameObject {
private:
	//singleton
	static PlayerManager* ptrInstance;

	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;

	static PlayerManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new PlayerManager;
		return *ptrInstance;
	};

	void privPlayerDied();
	void OnePlayerGameOver();
	void TwoPlayerSwitch();
	void TwoPlayerP1Died();
	void TwoPlayerGameOver();
	void privRegisterPlayer(Ship* sp);
	//change which player is active
	void privSetActivePlayer(int num);
	void privSetPlayerController(ShipController* pc);
	//access current player
	Ship* privGetCurrentPlayer();
	void privActivateTwoPlayer();
	void privDeactivateTwoPlayer();
	void privSetLevelControl(LevelController* lc);
	void privSetMushroomField(MushroomField* mf);
	void privSetDisplayText(DisplayText* pDt);

	//time to show "game over" text
	void Alarm1();
	//time to show "player 1" text
	void Alarm2();
	//time to show "player 2" text
	void Alarm3();
	//time between mushroom regen and respawn
	void Alarm4();
	//list of all players
	Ship* players[2];
	int PlayerLives[2] = { 3, 3 };
	Ship* CurrentPlayer;
	ShipController* PlayerController;
	LevelController* LevelControl;
	MushroomField* pM;
	DisplayText* dt;
	int PlayerCount;
	int CP;
	bool TwoPlayer;
	bool TwoPlayerDied;

	const float text_display = 3.0f;
	const float respawn_delay = 3.0f;
public: 
	static void SetActivePlayer(int num) { Instance().privSetActivePlayer(num); };
	static Ship* GetCurrentPlayer() { return Instance().privGetCurrentPlayer(); };
	static void PlayerDied() { Instance().privPlayerDied(); };
	static void ActivateTwoPlayer() { Instance().privActivateTwoPlayer(); };
	static void DeactivateTwoPlayer() { Instance().privDeactivateTwoPlayer(); };
	static void RegisterPlayer(Ship* sp) { Instance().privRegisterPlayer(sp); };
	static void SetPlayerController(ShipController* pc) { Instance().privSetPlayerController(pc); };
	static void SetLevelControl(LevelController* lc) { Instance().privSetLevelControl(lc); };
	static void SetMushroomField(MushroomField* mf) { Instance().privSetMushroomField(mf); };
	static void SetDisplayText(DisplayText* pDt) { Instance().privSetDisplayText(pDt); };

	static void Terminate();
};

#endif _PlayerManager