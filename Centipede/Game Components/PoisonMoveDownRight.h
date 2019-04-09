#ifndef _PoisonMoveDownRight
#define _PoisonMoveDownRight

#include "MoveState.h"

class PoisonMoveDownRight : public MoveState
{
public:
	PoisonMoveDownRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _PoisonMoveDownRight
