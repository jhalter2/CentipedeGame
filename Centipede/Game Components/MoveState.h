#ifndef _MoveState
#define _MoveState

struct OffsetArray;
struct RotationArray;
class CentipedeHead;

class MoveState
{
public:
	MoveState() {};
	const OffsetArray* GetMoveOffsets() const { return MyMoveOffsets; }
	const RotationArray* GetRotationOffsets() const { return MyRotationOffsets; }
	virtual const MoveState* GetNextState(CentipedeHead* chead) const = 0;

protected:
	const OffsetArray* MyMoveOffsets;
	const RotationArray* MyRotationOffsets;
};
#endif _MoveState
