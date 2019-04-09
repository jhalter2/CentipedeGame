#ifndef _MovementCollection
#define _MovementCollection


#include "TEAL\CommonElements.h"

struct OffsetArray
{
	sf::Vector2f Offsets[16];
	int row;
	int col;
	//int[16] rowoffset;
	//int[16] coloffset;

	OffsetArray(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, sf::Vector2f e, sf::Vector2f f, sf::Vector2f g,
		sf::Vector2f h, sf::Vector2f i, sf::Vector2f j, sf::Vector2f k, sf::Vector2f l, sf::Vector2f m, sf::Vector2f n,
		sf::Vector2f o, sf::Vector2f p, int y, int x) {
		Offsets[0] = a;
		Offsets[1] = b;
		Offsets[2] = c;
		Offsets[3] = d;
		Offsets[4] = e;
		Offsets[5] = f;
		Offsets[6] = g;
		Offsets[7] = h;
		Offsets[8] = i;
		Offsets[9] = j;
		Offsets[10] = k;
		Offsets[11] = l;
		Offsets[12] = m;
		Offsets[13] = n;
		Offsets[14] = o;
		Offsets[15] = p;
		row = y;
		col = x;
	};
};

class MovementCollection
{
public:
	static const OffsetArray OffsetsStraightRight;
	static const OffsetArray OffsetsTurnUpEndRight;
	static const OffsetArray OffsetsTurnDownEndRight;
	static const OffsetArray OffsetsStraightLeft;
	static const OffsetArray OffsetsTurnUpEndLeft;
	static const OffsetArray OffsetsTurnDownEndLeft;
};

#endif _MovementCollection