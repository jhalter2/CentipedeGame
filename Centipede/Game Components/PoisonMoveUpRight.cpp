#include <iostream>
#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "MoveRightAndDownwards.h"
#include "MoveRightAndUpwards.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnDownSwitchToLeft.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "PoisonMoveDown.h"
#include "PoisonMoveDownRight.h"
#include "PoisonMoveUpRight.h"
#include "PoisonMoveUpLeft.h"

PoisonMoveUpRight::PoisonMoveUpRight()
{
	//Initializing PoisonMoveUpright state

	MyMoveOffsets = &MovementCollection::OffsetsTurnUpEndRight;
	MyRotationOffsets = &RotationCollection::RotationOffsetsTurnUpEndRight;
}

const MoveState* PoisonMoveUpRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	float row = chead->GetRow();
	float col = chead->GetColumn() + 1; // looking ahead while right
										//need to get the field attached to the centipede head
	MushroomField::Obstacle obst = chead->GetField()->Inspect(row, col, chead->GetField());

	if (row == MushroomField::TOP_ROW) {
		pNextState = &MoveFSM::StateMoveRightAndDownwards;
	}
	else {
		pNextState = &MoveFSM::StatePoisonMoveUpLeft;
	}
	//if (obst == MushroomField::Obstacle::Clear)
	//{
	//	pNextState = &MoveFSM::StateMoveRightAndDownwards;
	//}
	//else if (obst == MushroomField::Obstacle::Blocked) // Edge, shroom or letter?
	//{
	//	if (row == MushroomField::BOTTOM_ROW)
	//		pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
	//	else
	//		pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
	//}
	//else // poison
	//{
	//	// Not implemented
	//	//assert(false && "Poison state not implemented yet!");
	//	//pNextState = nullptr;
	//}

	return pNextState;
}