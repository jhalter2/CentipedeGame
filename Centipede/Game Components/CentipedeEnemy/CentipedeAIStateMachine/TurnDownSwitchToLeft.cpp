#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "TurnDownSwitchToLeft.h"
#include "MoveLeftAndDownwards.h"
#include "TurnDownSwitchToRight.h"
#include "TurnUpSwitchToRight.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveDown.h"

TurnDownSwitchToLeft::TurnDownSwitchToLeft()
{
	//Initializing TurnDownSwitchToLeft state

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndLeft;
	MyRotationOffsets = &RotationCollection::RotationOffsetsTurnDownEndLeft;
}

const MoveState* TurnDownSwitchToLeft::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() - 1; // looking ahead after turn ->left
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndDownwards;
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomField::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnDownSwitchToRight;
		else
			pNextState = &MoveFSM::StateTurnUpSwitchToRight;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveDown;
	}

	return pNextState;
}
