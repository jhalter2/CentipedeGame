#ifndef _CentipedeBody
#define _CentipedeBody

#include "TEAL\CommonElements.h"
#include "MoveState.h"

class MushroomField;
class Bullet;
class PoisonMushroom;
class CentipedeHead;
class CmdScore;

class CentipedeBody : public GameObject {
public:
	CentipedeBody(CentipedeHead* pLead);
	CentipedeBody(CentipedeHead* pLead, CentipedeBody* pNext, CentipedeBody* pPrev);
	CentipedeBody(const CentipedeBody&);
	CentipedeBody & operator = (const CentipedeBody&);
	void Update();
	void Draw();
	void Destroy();
	virtual void Collision(GameObject *other) {};
	void Collision(Bullet *other);

	void ChangeAniState();

	void Initialize(CentipedeHead* pHead, CentipedeBody* pNext, CentipedeBody* pPrev);
	void SetHead(CentipedeHead* pNewHead);
	void SetNext(CentipedeBody* pNewNext);
	void SetPrev(CentipedeBody* pNewPrev);

	CentipedeHead* GetHead();
	CentipedeBody* GetNext();
	CentipedeBody* GetPrev();

	//set the moves we'll be using for the next 16 updates
	void SetNextMoves(sf::Vector2f NewMoves[16]);
	//set the rotation we'll be using for the next 16 updates
	void SetNextRotations(float NewRotations[16]);
	
	void SetPosition(sf::Vector2f NewPos);

	//once done, pass the moveset off to the next body part
	void NextBodyMoves(sf::Vector2f NewMoves[16]);
	void ResetNextMoves();
	void CancelMoves();
	//once done, pass the rotation set off to the next body part
	void NextBodyRotations(float NewRotations[16]);
	void ResetNextRotations();
	void CancelRotations();

	void CanMoveSwitch();
	void ChangePosition(sf::Vector2f move);

	void PromoteToHead();
	sf::Vector2f GetPosition();

private:
	CentipedeBody* pNext;
	CentipedeBody* pPrev;
	CentipedeHead* pHead;

	//for scoring
	CmdScore* pDeath;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;
	//holding the info for our moves and rotations that we get from the head
	sf::Vector2f Pos;
	sf::Vector2f NextMoves[16] = {};
	int MoveIndex;
	int AniState;
	float NextRotations[16] = { 0.0f };
	float speed;
	const float CELL_SIZE = 16.0f;
	const float HALF_CELL_SIZE = 8.0f;
	const float SCALE = 2.0f;
	const float X_START = 232.0f;
	const float Y_START = 8.0f;
	bool CanMove;

	
	//MushroomField* pM;
};
#endif _CentipedeBody

