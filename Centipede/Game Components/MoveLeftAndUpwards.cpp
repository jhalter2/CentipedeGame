#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "MoveLeftAndUpwards.h"
#include "TurnDownSwitchToRight.h"
#include "TurnUpSwitchToRight.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveUpRight.h"

MoveLeftAndUpwards::MoveLeftAndUpwards()
{
	//Initializing MoveLeftAndUpwards state

	MyMoveOffsets = &MovementCollection::OffsetsStraightLeft;
	MyRotationOffsets = &RotationCollection::RotationOffsetsStraightLeft;
}

const MoveState* MoveLeftAndUpwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() - 1; // looking ahead while left
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndUpwards;
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomField::TOP_PLAYER_ROW)
			pNextState = &MoveFSM::StateTurnDownSwitchToRight;
		else
			pNextState = &MoveFSM::StateTurnUpSwitchToRight;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveUpRight;
	}

	return pNextState;
}