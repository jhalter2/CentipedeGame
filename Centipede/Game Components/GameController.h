#ifndef _GameController
#define _GameController

#include "TEAL\CommonElements.h"

class GameController
{
private:
	static GameController* ptrInstance;							// set up as a singleton

	GameController();											// Private constructor 
	GameController(const GameController&) = delete;				// Prevent copy-construction
	GameController& operator=(const GameController&) = delete;	// Prevent assignment

	static GameController& Instance()							// Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new GameController;
		return *ptrInstance;
	};

	void ResetScore();
	void AddScore(int v);
	int GetScore();

	void PlayerDies();

	static const int GameAreaTop = 480;
	static const int GameAreaBottom = 0;
	static const int GameAreaRight = 512;
	static const int GameAreaLeft = 0;

	int Score;
public:

	static void Terminate();
};

#endif _GameController
