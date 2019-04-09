#ifndef _Explosion
#define _Explosion

#include "TEAL\CommonElements.h"

class Explosion : public GameObject {
public:
	Explosion();
	void Initialize(sf::Vector2f pos);

	void Update();
	void Draw();

	void ChangeAni();
private:
	sf::Vector2f Position;
	AnimatedSprite MainSprite;

	int AniState;
};

#endif _Explosion
