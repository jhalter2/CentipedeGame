#ifndef _Scorpion
#define _Scorpion

#include "TEAL\CommonElements.h"

class Mushroom;
class PoisonMushroom;
class Bullet;
class MushroomField;
class CmdScore;

class Scorpion : public GameObject {
public:
	Scorpion();
	//need to initialize after recycling
	void Initialize(MushroomField* pF, sf::Vector2f, float speed, float direction);
	void Update();
	void Draw();
	void Destroy();

	virtual void Collision(GameObject *go) {};
	void Collision(Bullet *other);
	void Collision(Mushroom *other);
	//change animation with movement
	void ChangeAni();
	void Die();
	void FieldClear();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	//for scoring
	CmdScore* pDeath;

	MushroomField* pM;
	int AniState;
	int steps;
	int rand1;
	int rand2;
	const float cell_size = 16.0f;
	float direction;
	float speed;
	float scale;


};
#endif _Scorpion

