#ifndef _MoveRightAndUpwards
#define _MoveRightAndUpwards

#include "MoveState.h"

class MoveRightAndUpwards : public  MoveState
{
public:
	MoveRightAndUpwards();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _MoveRightAndUpwards
