#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "MoveRightAndDownwards.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnDownSwitchToLeft.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveDown.h"

MoveRightAndDownwards::MoveRightAndDownwards()
{
	//Initializing MoveRightAndDownwards state

	MyMoveOffsets = &MovementCollection::OffsetsStraightRight;
	MyRotationOffsets = &RotationCollection::RotationOffsetsStraightRight;
}

const MoveState* MoveRightAndDownwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() + 1; // looking ahead while right
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndDownwards;
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomField::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
		else
			pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveDown;
	}

	return pNextState;
}