#ifndef _PoisonMoveUpLeft
#define _PoisonMoveUpLeft

#include "MoveState.h"

class PoisonMoveUpLeft : public MoveState
{
public:
	PoisonMoveUpLeft();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _PoisonMoveUpLeft
