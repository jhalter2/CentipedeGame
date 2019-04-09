#ifndef _RotationCollection
#define _RotationCollection


#include "TEAL\CommonElements.h"

struct RotationArray
{
	float RotationOffsets[16];

	RotationArray(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, 
		float n, float o, float p) {
		RotationOffsets[0] = a;
		RotationOffsets[1] = b;
		RotationOffsets[2] = c;
		RotationOffsets[3] = d;
		RotationOffsets[4] = e;
		RotationOffsets[5] = f;
		RotationOffsets[6] = g;
		RotationOffsets[7] = h;
		RotationOffsets[8] = i;
		RotationOffsets[9] = j;
		RotationOffsets[10] = k;
		RotationOffsets[11] = l;
		RotationOffsets[12] = m;
		RotationOffsets[13] = n;
		RotationOffsets[14] = o;
		RotationOffsets[15] = p;
	};
};

class RotationCollection
{
public:
	static const RotationArray RotationOffsetsStraightRight;
	static const RotationArray RotationOffsetsTurnUpEndRight;
	static const RotationArray RotationOffsetsTurnDownEndRight;
	static const RotationArray RotationOffsetsStraightLeft;
	static const RotationArray RotationOffsetsTurnUpEndLeft;
	static const RotationArray RotationOffsetsTurnDownEndLeft;
};

#endif _RotationCollection
