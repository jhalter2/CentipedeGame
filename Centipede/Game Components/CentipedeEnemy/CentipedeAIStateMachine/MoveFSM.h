#ifndef _MoveFSM
#define _MoveFSM

class MoveRightAndDownwards;
class MoveRightAndUpwards;
class MoveLeftAndDownwards;
class MoveLeftAndUpwards;
class TurnDownSwitchToLeft;
class TurnDownSwitchToRight;
class TurnUpSwitchToLeft;
class TurnUpSwitchToRight;
class PoisonMoveDown;
class PoisonMoveDownRight;
class PoisonMoveUpLeft;
class PoisonMoveUpRight;

class MoveFSM
{
private:

public:
	static const MoveRightAndDownwards StateMoveRightAndDownwards;
	static const MoveRightAndUpwards StateMoveRightAndUpwards;
	static const MoveLeftAndDownwards StateMoveLeftAndDownwards;
	static const MoveLeftAndUpwards StateMoveLeftAndUpwards;
	static const TurnDownSwitchToLeft StateTurnDownSwitchToLeft;
	static const TurnDownSwitchToRight StateTurnDownSwitchToRight;
	static const TurnUpSwitchToLeft StateTurnUpSwitchToLeft;
	static const TurnUpSwitchToRight StateTurnUpSwitchToRight;
	static const PoisonMoveDown StatePoisonMoveDown;
	static const PoisonMoveDownRight StatePoisonMoveDownRight;
	static const PoisonMoveUpLeft StatePoisonMoveUpLeft;
	static const PoisonMoveUpRight StatePoisonMoveUpRight;

};

#endif _MoveFSM
