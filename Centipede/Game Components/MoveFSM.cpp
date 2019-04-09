#include "MoveFSM.h"

#include "MoveRightAndDownwards.h"
#include "MoveRightAndUpwards.h"
#include "MoveLeftAndDownwards.h"
#include "MoveLeftAndUpwards.h"
#include "TurnDownSwitchToLeft.h"
#include "TurnDownSwitchToRight.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnUpSwitchToRight.h"
#include "PoisonMoveDown.h"
#include "PoisonMoveDownRight.h"
#include "PoisonMoveUpLeft.h"
#include "PoisonMoveUpRight.h"

const MoveRightAndDownwards MoveFSM::StateMoveRightAndDownwards;
const MoveRightAndUpwards MoveFSM::StateMoveRightAndUpwards;
const MoveLeftAndDownwards MoveFSM::StateMoveLeftAndDownwards;
const MoveLeftAndUpwards MoveFSM::StateMoveLeftAndUpwards;
const TurnDownSwitchToLeft MoveFSM::StateTurnDownSwitchToLeft;
const TurnDownSwitchToRight MoveFSM::StateTurnDownSwitchToRight;
const TurnUpSwitchToLeft MoveFSM::StateTurnUpSwitchToLeft;
const TurnUpSwitchToRight MoveFSM::StateTurnUpSwitchToRight;
const PoisonMoveDown MoveFSM::StatePoisonMoveDown;
const PoisonMoveDownRight MoveFSM::StatePoisonMoveDownRight;
const PoisonMoveUpLeft MoveFSM::StatePoisonMoveUpLeft;
const PoisonMoveUpRight MoveFSM:: StatePoisonMoveUpRight;