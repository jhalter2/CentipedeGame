#ifndef _CentipedeHead
#define _CentipedeHead

#include "TEAL\CommonElements.h"
#include "MoveState.h"

class MushroomField;
class Bullet;
class PoisonMushroom;
class CentipedeBody;
class CmdScore;
class Ship;

class CentipedeHead : public GameObject
{
public:
	CentipedeHead();
	void Update();
	void Draw();
	void Destroy();
	virtual void Collision(GameObject* other) {};
	void Collision(Bullet *other);
	void Collision(Ship* other);
	//initialize values when recycled 
	void Initialize(sf::Vector2f p, MushroomField* pF, float s, float col, int body);
	float GetRow();
	float GetColumn();
	//need to set when we promote bodies to heads
	void SetRow(float r);
	void SetCol(float c);

	void SetRotation(float degrees);

	void MoveBody(sf::Vector2f mov);

	void ChangeAniState();

	//useful functions when promoting body parts to heads
	int GetBodyLength();
	void SetBodyLength(int length);
	//set the first body segment immediately behind the head
	void SetNext(CentipedeBody* pBody);
	
	//create new head when destroyed
	void CreateNewHead();
	void FixBodyPointers(CentipedeHead* pH);

	//useful functions when body gets promoted to head
	MushroomField* GetField();
	CentipedeBody* GetNext();
	float GetXPosition();
	float GetYPosition();
	float GetSpeed();
	//get rid of head and body parts when player dies
	void DeathReset();
private:
	sf::Vector2f Pos;
	//track previous move and previous rotation for body pieces
	sf::Vector2f PrevMove[16] = {};
	float PrevRot[16] = {0.0f};

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	MushroomField* pM;
	const MoveState* pCurrentState;

	//list of body parts
	CentipedeBody* next;

	//for scoring
	CmdScore* pDeath;

	int CheckCount;
	int StepCount;
	int OffsetIndex;
	int AniState;
	int bodyLength;
	float CurrRow;
	float CurrCol;
	float RotOffset;
	float speed;
	const float CELL_SIZE = 16.0f;
	const float HALF_CELL_SIZE = 8.0f;
	const float HEAD_SCALE = 2.0f;
};
#endif _CentipedeHead

