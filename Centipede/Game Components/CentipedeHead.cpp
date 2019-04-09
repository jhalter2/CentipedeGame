#include "CentipedeHead.h"
#include "Bullet.h"
#include "PoisonMushroom.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "TurnDownSwitchToRight.h"
#include "MoveState.h"
#include "MovementCollection.h"
#include "RotationCollection.h"
#include "CentipedeBody.h"
#include "ScoreManager.h"
#include "CentipedeHeadFactory.h"
#include "ExplosionFactory.h"
#include "Ship.h"
#include "SoundManager.h"
#include "CentipedeManager.h"

CentipedeHead::CentipedeHead() {
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeHeadKilled);

	

	bitmap = &ResourceManager::GetTextureBitmap("CentipedeHead");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeHead"), 8, 2);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / HEAD_SCALE, MainSprite.getTextureRect().height / HEAD_SCALE);
	MainSprite.setScale(HEAD_SCALE, HEAD_SCALE);

	SetCollider(MainSprite, *bitmap);
}

void CentipedeHead::Initialize(sf::Vector2f p, MushroomField* pF, float s, float col, int body) {
	pM = pF;
	AniState = 1;
	StepCount = 0;
	//centipede body list
	next = 0;
	//need to know row and column centipede is on
	CurrRow = 0.0f;
	OffsetIndex = 0;
	RotOffset = 0;
	MainSprite.setRotation(0);
	pCurrentState = &MoveFSM::StateTurnDownSwitchToRight;
	pM = pF;
	Pos = p;
	speed = s;
	CurrCol = col;
	bodyLength = body;
	MainSprite.setPosition(Pos);
	RegisterCollision<CentipedeHead>(*this);
}

void CentipedeHead::Update() {
	MainSprite.Update();

	//move
	Pos += pCurrentState->GetMoveOffsets()->Offsets[OffsetIndex] * speed;
	//move the body parts from previous move then store the new move for next update
	PrevMove[OffsetIndex] = pCurrentState->GetMoveOffsets()->Offsets[OffsetIndex] * speed;
	
	//rotate when needed
	RotOffset += pCurrentState->GetRotationOffsets()->RotationOffsets[OffsetIndex] * speed;
	PrevRot[OffsetIndex] = RotOffset;
	MainSprite.setRotation(RotOffset);

	OffsetIndex += 1;
	StepCount += (int)speed;
	if (StepCount >= 16) {
		//change animation
		ChangeAniState();
		//pass off our move array and rotation array to the body once we have them
		if (this->next != 0) {
			this->next->CanMoveSwitch();
			this->next->SetNextMoves(PrevMove);
			this->next->SetNextRotations(PrevRot);
		}
		//add row, check state, then add col
		CurrRow += (pCurrentState->GetMoveOffsets())->row;
		pCurrentState = pCurrentState->GetNextState(this);
		OffsetIndex = 0;
		StepCount = 0;
		CurrCol += (pCurrentState->GetMoveOffsets())->col;
	}

	MainSprite.setPosition(Pos);
}

void CentipedeHead::Draw() {
	WindowManager::MainWindow.draw(MainSprite);
}

void CentipedeHead::Destroy() {
	DeregisterCollision<CentipedeHead>(*this);
}

float CentipedeHead::GetXPosition() {
	return Pos.x;
}

float CentipedeHead::GetYPosition() {
	return Pos.y;
}

void CentipedeHead::Collision(Bullet* other) {
	//need to set up a new head if there are body segments attached
	ScoreManager::SendScoreCmd(pDeath);
	if (next != 0) {
		CreateNewHead();
	}
	sf::Vector2f NewPos(pM->NearestCell(Pos.x), Pos.y + HALF_CELL_SIZE);
	pM->SpawnOneShroom(NewPos);
	ExplosionFactory::CreateExplosion(Pos);
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
	CentipedeManager::CentipedeHeadDied(this);
	MarkForDestroy();
}

void CentipedeHead::Collision(Ship* other) {
	//need to reset everything since player died
	ExplosionFactory::CreateExplosion(Pos);
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
	MarkForDestroy();
}

float CentipedeHead::GetRow() {
	return CurrRow;
}

float CentipedeHead::GetColumn() {
	return CurrCol;
}

void CentipedeHead::SetRow(float r) {
	CurrRow = r;
}

void CentipedeHead::SetCol(float c) {
	CurrCol = c;
}


MushroomField* CentipedeHead::GetField() {
	return pM;
}

void CentipedeHead::SetRotation(float degrees) {
	MainSprite.setRotation(degrees);
}

void CentipedeHead::MoveBody(sf::Vector2f mov) {
	CentipedeBody* pC = this->next;
	while (pC != 0) {
		//go through our last and trickle down the movement commands from head to body parts
		pC->ChangePosition(mov);
		pC = pC->GetNext();
	}
}

void CentipedeHead::SetNext(CentipedeBody* pBody) {
	this->next = pBody;
}

void CentipedeHead::ChangeAniState() {
	MainSprite.SetAnimation(AniState, AniState, false, false);
	if (AniState == 7) AniState = 1;
	else AniState++;
}

CentipedeBody* CentipedeHead::GetNext() {
	return next;
}

void CentipedeHead::CreateNewHead() {
	float NewColumn;
	if (next->GetPosition().x > Pos.x) NewColumn = CurrCol + 1.0f;
	else NewColumn = CurrCol - 1.0f;
	sf::Vector2f NewPosition = sf::Vector2f((NewColumn * CELL_SIZE) + HALF_CELL_SIZE, (CurrRow * CELL_SIZE) + HALF_CELL_SIZE);
	CentipedeHead* ch = CentipedeManager::MakeCentipedeHead(NewPosition, GetField(), speed, NewColumn, 0);
	ch->SetRow(CurrRow);
	FixBodyPointers(ch);
	
}

void CentipedeHead::FixBodyPointers(CentipedeHead* pH) {
	//fix body pointers and positions
	int NumBody = 1;
	if (next->GetNext() != 0) {
		CentipedeBody* pNextBody = next;
		CentipedeBody* pCB = next->GetNext();
		if (next->GetPosition().x < Pos.x) {
			while (pCB != 0) {
				pCB->SetHead(pH);
				pCB->SetPosition(sf::Vector2f((pH->GetColumn() * CELL_SIZE) - (HALF_CELL_SIZE * (float)NumBody), (CurrRow * CELL_SIZE) + HALF_CELL_SIZE));
				pCB = pCB->GetNext();
				NumBody += 2;
			}
		}
		else {
			while (pCB != 0) {
				pCB->SetHead(pH);
				pCB->SetPosition(sf::Vector2f((pH->GetColumn() * CELL_SIZE) + (HALF_CELL_SIZE * (float)NumBody), (CurrRow * CELL_SIZE) + HALF_CELL_SIZE));
				pCB = pCB->GetNext();
				NumBody += 2;
			}
		}
		pH->SetNext(next->GetNext());
		next->SetPrev(0);
		pNextBody->SetPrev(0);
		pNextBody->SetNext(0);
		pNextBody->MarkForDestroy();		
	}
	else {
		CentipedeBody* pNextBody = next;
		next->SetPrev(0);
		pNextBody->SetPrev(0);
		pNextBody->SetNext(0);
		pNextBody->MarkForDestroy();
	}
}

float CentipedeHead::GetSpeed() {
	return speed;
}

int CentipedeHead::GetBodyLength() {
	return bodyLength;
}

void CentipedeHead::SetBodyLength(int length) {
	bodyLength = length;
}

void CentipedeHead::DeathReset() {
	if (next != 0) {
		if (next->GetNext() != 0) {
			CentipedeBody* pB = next;
			CentipedeBody* pB2;
			while (pB != 0) {
				if (pB->GetNext() != 0) pB2 = pB->GetNext();
				else pB2 = 0;
				pB->SetHead(0);
				pB->SetNext(0);
				pB->SetPrev(0);
				pB->MarkForDestroy();
				if (pB2 != 0) pB = pB2;
				else pB = 0;
			}
		}
		else {
			next->SetHead(0);
			next->MarkForDestroy();
		}
		next = 0;
	}
	CentipedeManager::RemoveCentipedeHead(this);
	MarkForDestroy();
}