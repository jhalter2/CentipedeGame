#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "TurnUpSwitchToRight.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnDownSwitchToLeft.h"
#include "MoveRightAndUpwards.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveUpLeft.h"

TurnUpSwitchToRight::TurnUpSwitchToRight()
{
	//Initializing TurnUpSwitchToRight state

	MyMoveOffsets = &MovementCollection::OffsetsTurnUpEndRight;
	MyRotationOffsets = &RotationCollection::RotationOffsetsTurnUpEndRight;
}

const MoveState* TurnUpSwitchToRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() + 1; // looking ahead after turn -> Right
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndUpwards;
		
	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomField::TOP_PLAYER_ROW)
			pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
		else
			pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveUpLeft;
	}

	return pNextState;
}