#ifndef _MoveLeftAndDownwards
#define _MoveLeftAndDownwards

#include "MoveState.h"

class MoveLeftAndDownwards : public  MoveState
{
public:
	MoveLeftAndDownwards();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _MoveLeftAndDownwards
