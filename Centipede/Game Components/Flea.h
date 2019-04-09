#ifndef _Flea
#define _Flea

#include "TEAL\CommonElements.h"

class Bullet;
class Mushroom;
class Ship;
class MushroomField;
class PoisonMushroom;

class Flea : public GameObject 
{
public:
	Flea(MushroomField* pF);
	void Initialize(sf::Vector2f p, MushroomField* pF);
	void Update();
	void Draw();
	void Destroy();
	void SpawnMushroom();

	void ChangeAniState();

	virtual void Collision(GameObject *other) {};
	void Collision(Bullet *other);
	void Collision(Ship *other);
	void Die();
	void FieldClear();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	int health;
	int spawn;
	int steps;
	int rand1;
	int AniState;
	int speed;
	MushroomField* pM;
	const float cell_size = 16.0f;
	float scale;
	float row;
	float col;
	float TimeBetween;
	bool CanSpawn;
};
#endif _Flea

