#ifndef _PoisonMoveUpRight
#define _PoisonMoveUpRight

#include "MoveState.h"

class PoisonMoveUpRight : public MoveState
{
public:
	PoisonMoveUpRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _PoisonMoveUpRight
