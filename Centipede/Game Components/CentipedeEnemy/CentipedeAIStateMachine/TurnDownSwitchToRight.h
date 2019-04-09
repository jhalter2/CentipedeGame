#ifndef _TurnDownSwitchToRight
#define _TurnDownSwitchToRight

#include "MoveState.h"
class TurnDownSwitchToRight : public  MoveState
{
public:
	TurnDownSwitchToRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _TurnDownSwitchToRight
