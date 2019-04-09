#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "TurnDownSwitchToRight.h"
#include "MoveRightAndDownwards.h"
#include "TurnDownSwitchToLeft.h"
#include "TurnUpSwitchToLeft.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveDownRight.h"

TurnDownSwitchToRight::TurnDownSwitchToRight()
{
	//Initializing TurnDownSwitchToRight state

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndRight;
	MyRotationOffsets = &RotationCollection::RotationOffsetsTurnDownEndRight;
}

const MoveState* TurnDownSwitchToRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() + 1; // looking ahead after turn -> right
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndDownwards;
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomField::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
		else
			pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveDownRight;
	}

	return pNextState;
}