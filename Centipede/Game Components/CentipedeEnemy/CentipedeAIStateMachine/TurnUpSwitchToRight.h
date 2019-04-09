#ifndef _TurnUpSwitchToRight
#define _TurnUpSwitchToRight

#include "MoveState.h"
class TurnUpSwitchToRight : public  MoveState
{
public:
	TurnUpSwitchToRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _TurnUpSwitchToRight
