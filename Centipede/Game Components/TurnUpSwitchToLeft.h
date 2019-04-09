#ifndef _TurnUpSwitchToLeft
#define _TurnUpSwitchToLeft

#include "MoveState.h"
class TurnUpSwitchToLeft : public MoveState
{
public:
	TurnUpSwitchToLeft();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
};

#endif _TurnUpSwitchToLeft