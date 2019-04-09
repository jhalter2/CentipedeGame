#ifndef _PoisonMoveDown
#define _PoisonMoveDown

#include "MoveState.h"

class PoisonMoveDown : public MoveState
{
public:
	PoisonMoveDown();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _PoisonMoveDown
