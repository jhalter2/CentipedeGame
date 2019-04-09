#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnUpSwitchToRight.h"
#include "MoveLeftAndUpwards.h"
#include "TurnDownSwitchToRight.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveUpRight.h"

TurnUpSwitchToLeft::TurnUpSwitchToLeft()
{
	//Initializing TurnUpSwitchToLeft state

	MyMoveOffsets = &MovementCollection::OffsetsTurnUpEndLeft;
	MyRotationOffsets = &RotationCollection::RotationOffsetsTurnUpEndLeft;
}

const MoveState* TurnUpSwitchToLeft::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() - 1; // looking ahead after turn -> left
	//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (obst == MushroomField::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndUpwards;
		//chead->SetScale(2.0f, 2.0f);

	}
	else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomField::TOP_PLAYER_ROW + 1.0f)
			pNextState = &MoveFSM::StateTurnUpSwitchToRight;
		else
			pNextState = &MoveFSM::StateTurnDownSwitchToRight;
	}
	else // poison
	{
		pNextState = &MoveFSM::StatePoisonMoveUpRight;
	}

	return pNextState;
}