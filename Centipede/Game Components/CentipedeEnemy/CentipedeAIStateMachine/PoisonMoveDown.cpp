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
#include "PoisonMoveDownRight.h"
#include "MoveLeftAndUpwards.h"

PoisonMoveDown::PoisonMoveDown()
{
	//Initializing PoisonMoveDown state

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndLeft;
	MyRotationOffsets = &RotationCollection::RotationOffsetsTurnDownEndLeft;
}

const MoveState* PoisonMoveDown::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() + 1; // looking ahead while right
									  //need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (row == MushroomField::BOTTOM_ROW) {
		pNextState = &MoveFSM::StateMoveLeftAndUpwards;
	}
	else {
		pNextState = &MoveFSM::StatePoisonMoveDownRight;
	}

	return pNextState;
}
