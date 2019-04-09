#include "RotationCollection.h"

//put the rotation values in that we'll need for each state of the centipedehead FSM

const RotationArray RotationCollection::RotationOffsetsStraightRight = RotationArray(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

const RotationArray RotationCollection::RotationOffsetsTurnUpEndRight = RotationArray(11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f,
	11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25);

const RotationArray RotationCollection::RotationOffsetsTurnDownEndRight = RotationArray(-11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f,
	-11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f);

const RotationArray RotationCollection::RotationOffsetsStraightLeft = RotationArray(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

const RotationArray RotationCollection::RotationOffsetsTurnUpEndLeft = RotationArray(-11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f,
	-11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f, -11.25f);

const RotationArray RotationCollection::RotationOffsetsTurnDownEndLeft = RotationArray(11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f,
	11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25f, 11.25);