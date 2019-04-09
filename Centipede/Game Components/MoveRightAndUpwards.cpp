#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "MoveRightAndUpwards.h"
#include "TurnDownSwitchToLeft.h"
#include "TurnUpSwitchToLeft.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"

MoveRightAndUpwards::MoveRightAndUpwards()
{
	//Initializing MoveRightAndUpwards state

	MyMoveOffsets = &MovementCollection::OffsetsStraightRight;
	MyRotationOffsets = &RotationCollection::RotationOffsetsStraightRight;
}

const MoveState* MoveRightAndUpwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() + 1; // looking ahead while right
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndUpwards;
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomField::TOP_PLAYER_ROW)
			pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
		else
			pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
	}
	else // poison
	{
		// Not implemented
		//assert(false && "Poison state not implemented yet!");
		//pNextState = nullptr;
	}

	return pNextState;
}