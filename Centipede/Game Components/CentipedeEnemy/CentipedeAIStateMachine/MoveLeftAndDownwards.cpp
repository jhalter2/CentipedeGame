#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "MoveLeftAndDownwards.h"
#include "TurnUpSwitchToRight.h"
#include "TurnDownSwitchToRight.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveDownRight.h"

MoveLeftAndDownwards::MoveLeftAndDownwards()
{
	//Initializing MoveLeftAndDownwards state

	MyMoveOffsets = &MovementCollection::OffsetsStraightLeft;
	MyRotationOffsets = &RotationCollection::RotationOffsetsStraightLeft;
}

const MoveState* MoveLeftAndDownwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() - 1; // looking ahead while left
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndDownwards;
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomField::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnUpSwitchToRight;
		else
			pNextState = &MoveFSM::StateTurnDownSwitchToRight;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveDownRight;
	}

	return pNextState;
}
