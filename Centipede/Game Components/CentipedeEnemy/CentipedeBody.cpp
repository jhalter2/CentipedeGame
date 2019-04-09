#include "CentipedeBody.h"
#include "CentipedeHead.h"
#include "Bullet.h"
#include "MushroomField.h"
#include "ScoreManager.h"
#include "ExplosionFactory.h"
#include "SoundManager.h"
#include "CentipedeManager.h"

CentipedeBody::CentipedeBody(CentipedeHead* pLead) {
	//initialize the list elements
	pHead = pLead;
	pNext = 0;
	pPrev = 0;


	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeBodyKilled);

	bitmap = &ResourceManager::GetTextureBitmap("CentipedeBody");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeBody"), 8, 2);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2.0f, 2.0f);
	MainSprite.setPosition(Pos);

	Pos = sf::Vector2f(X_START, Y_START);

	SetCollider(MainSprite, *bitmap);
	
}

CentipedeBody::CentipedeBody(CentipedeHead* pLead, CentipedeBody* pNext, CentipedeBody* pPrev) {
	//initialize the list elements
	pHead = pLead;
	this->pNext = pNext;
	this->pPrev = pPrev;
	

	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeBodyKilled);

	bitmap = &ResourceManager::GetTextureBitmap("CentipedeBody");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeBody"), 8, 2);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / SCALE, MainSprite.getTextureRect().height / SCALE);
	MainSprite.setScale(SCALE, SCALE);
	MainSprite.setPosition(Pos);

	Pos = sf::Vector2f(X_START, Y_START);

	SetCollider(MainSprite, *bitmap);
}

void CentipedeBody::Initialize(CentipedeHead* pHead, CentipedeBody* pNext, CentipedeBody* pPrev) {
	this->pHead = pHead;
	this->pNext = pNext;
	this->pPrev = pPrev;
	speed = pHead->GetSpeed();
	MainSprite.setRotation(0);
	MoveIndex = 0;
	AniState = 0;
	CanMove = false;
	CancelMoves();
	CancelRotations();
	Pos = sf::Vector2f(X_START, Y_START);
	RegisterCollision<CentipedeBody>(*this);
}


CentipedeBody::CentipedeBody(const CentipedeBody &tmp) {

	this->pNext = tmp.pNext;
	this->pPrev = tmp.pPrev;
	this->pHead = tmp.pHead;
}

CentipedeBody & CentipedeBody::operator = (const CentipedeBody &tmp) {

	this->pNext = tmp.pNext;
	this->pPrev = tmp.pPrev;
	this->pHead = tmp.pHead;

	return *this;
}

void CentipedeBody::Update() {
	MainSprite.Update();

	if (CanMove == true) {
		//add the offset to our position
		Pos += NextMoves[MoveIndex];
		MainSprite.setRotation(NextRotations[MoveIndex]);
		MoveIndex++;

		if (MoveIndex >= 16 / (int)speed) {
			ChangeAniState();
			if (pNext != 0) {
				//if there is a next, hand off the moves and rotations
				this->pNext->CanMoveSwitch();
				this->NextBodyMoves(NextMoves);
				this->NextBodyRotations(NextRotations);
			}
			MoveIndex = 0;
		}
	}
	MainSprite.setPosition(Pos);
}

void CentipedeBody::Draw() {
	WindowManager::MainWindow.draw(MainSprite);
}

void CentipedeBody::Destroy() {
	DeregisterCollision<CentipedeBody>(*this);
}

void CentipedeBody::Collision(Bullet *other) {
	ScoreManager::SendScoreCmd(pDeath);
	ExplosionFactory::CreateExplosion(Pos);
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
	PromoteToHead();
}

void CentipedeBody::SetHead(CentipedeHead* pNewHead) {
	this->pHead = pNewHead;
}

void CentipedeBody::SetNext(CentipedeBody* pNewNext) {
	this->pNext = pNewNext;
}

void CentipedeBody::SetPrev(CentipedeBody* pNewPrev) {
	this->pPrev = pNewPrev;
}

CentipedeHead* CentipedeBody::GetHead() {
	return this->pHead;
}

CentipedeBody* CentipedeBody::GetNext() {
	return this->pNext;
}

CentipedeBody* CentipedeBody::GetPrev() {
	return this->pPrev;
}

void CentipedeBody::ChangePosition(sf::Vector2f move) {
	this->Pos += move;
}

void CentipedeBody::SetNextMoves(sf::Vector2f NewMoves[16]) {
	for (int i = 0; i < 16; i++) {
		this->NextMoves[i] = NewMoves[i];
	}
}

void CentipedeBody::SetNextRotations(float NewRotations[16]) {
	for (int i = 0; i < 16; i++) {
		this->NextRotations[i] = NewRotations[i];
	}
}

void CentipedeBody::SetPosition(sf::Vector2f NewPos) {
	Pos = NewPos;
}


void CentipedeBody::NextBodyMoves(sf::Vector2f NewMoves[16]) {
	if (this->pNext != 0) {
		for (int i = 0; i < 16; i++) {
			this->pNext->NextMoves[i] = NewMoves[i];
		}
	}
}

void CentipedeBody::ResetNextMoves() {
	if (this->pNext != 0) {
		for (int i = 0; i < 16; i++) {
			this->pNext->NextMoves[i] = sf::Vector2f(0.0f, 0.0f);
		}
	}
}

void CentipedeBody::CancelMoves() {
	for (int i = 0; i < 16; i++) {
		NextMoves[i] = sf::Vector2f(0.0f, 0.0f);
	}
	MoveIndex = 0;
}

void CentipedeBody::NextBodyRotations(float NewRotations[16]) {
	if (this->pNext != 0) {
		for (int i = 0; i < 16; i++) {
			this->pNext->NextRotations[i] = NewRotations[i];
		}
	}
}

void CentipedeBody::ResetNextRotations() {
	if (this->pNext != 0) {
		for (int i = 0; i < 16; i++) {
			this->pNext->NextMoves[i] = sf::Vector2f(0.0f, 0.0f);
		}
	}
}

void CentipedeBody::CancelRotations() {
	for (int i = 0; i < 16; i++) {
		NextRotations[i] = 0.0f;
	}
	MoveIndex = 0;
}

void CentipedeBody::CanMoveSwitch() {
	CanMove = true;
}

void CentipedeBody::ChangeAniState() {
	MainSprite.SetAnimation(AniState, AniState, false, false);
	if (AniState == 7) AniState = 1;
	else AniState++;
}

void CentipedeBody::PromoteToHead() {
	//first body part after head
	if (pPrev == 0) {
		//no body parts after
		if (pNext == 0) {
			sf::Vector2f NewPos(pHead->GetField()->NearestCell(Pos.x), Pos.y + HALF_CELL_SIZE);
			pHead->GetField()->SpawnOneShroom(NewPos);
			pHead->SetNext(0);
			pHead = 0;
		}
		//body parts after
		else {
			sf::Vector2f NewPos(pHead->GetField()->NearestCell(Pos.x), Pos.y + HALF_CELL_SIZE);
			pHead->GetField()->SpawnOneShroom(NewPos);
			CentipedeHead* ch;
			if (Pos.x < pHead->GetXPosition()) {
				ch = CentipedeManager::MakeCentipedeHead(sf::Vector2f(pHead->GetField()->NearestCell(pNext->GetPosition().x), pNext->GetPosition().y),
					pHead->GetField(), pHead->GetSpeed(), pHead->GetColumn(), pHead->GetBodyLength());
			}
			else {
				ch = CentipedeManager::MakeCentipedeHead(sf::Vector2f(pHead->GetField()->NearestCell(pNext->GetPosition().x), pNext->GetPosition().y),
					pHead->GetField(), pHead->GetSpeed(), pHead->GetColumn(), pHead->GetBodyLength());
			}

			ch->SetCol(pHead->GetField()->NearestCell(ch->GetXPosition()) / CELL_SIZE);
			ch->SetRow(pHead->GetRow());
			pHead->SetNext(0);
			if (pNext->GetNext() != 0) {
				ch->SetNext(pNext->GetNext());
				pNext->GetNext()->pPrev = 0;
				//adjust head pointers in body
				CentipedeBody* pCb = pNext->GetNext();
				while (pCb != 0) {
					pCb->ResetNextMoves();
					pCb->ResetNextRotations();
					pCb->pHead = ch;
					pCb = pCb->GetNext();
				}
			}
			else {
				ch->SetNext(0);
			}
			pNext->pPrev = 0;
			pNext->pNext = 0;
			pNext->pHead = 0;
			pNext->MarkForDestroy();
			pNext = 0;
			pHead = 0;
		}	
	}
	//last body part
	else if (pNext == 0){
		sf::Vector2f NewPos(pHead->GetField()->NearestCell(Pos.x), Pos.y + HALF_CELL_SIZE);
		pHead->GetField()->SpawnOneShroom(NewPos);
		pPrev->pNext = 0;
		pPrev = 0;
		pHead = 0;
	}
	//body part in middle
	else {
  		sf::Vector2f NewPos(pHead->GetField()->NearestCell(Pos.x), Pos.y + HALF_CELL_SIZE);
		pHead->GetField()->SpawnOneShroom(NewPos);
		CentipedeHead* ch;
		if (Pos.x < pHead->GetXPosition()) {
			ch = CentipedeManager::MakeCentipedeHead(sf::Vector2f(pHead->GetField()->NearestCell(pNext->GetPosition().x), pNext->GetPosition().y),
				pHead->GetField(), pHead->GetSpeed(), pHead->GetColumn(), pHead->GetBodyLength());
		}
		else {
			ch = CentipedeManager::MakeCentipedeHead(sf::Vector2f(pHead->GetField()->NearestCell(pNext->GetPosition().x), pNext->GetPosition().y),
				pHead->GetField(), pHead->GetSpeed(), pHead->GetColumn(), pHead->GetBodyLength());
		}

		ch->SetCol(pHead->GetField()->NearestCell(ch->GetXPosition()) / CELL_SIZE);
		ch->SetRow(pHead->GetRow());
		if (pNext->GetNext() != 0) {
			ch->SetNext(pNext->GetNext());
			//adjust head pointers in body
			CentipedeBody* pCb = pNext->GetNext();
			while (pCb != 0) {
				pCb->pHead = ch;
				pCb = pCb->GetNext();
			}
		}
		else {
			ch->SetNext(0);
		}
		pPrev->pNext = 0;
		pPrev = 0;
		pHead = 0;
		pNext->pPrev = 0;
		pNext->pHead = 0;
		if (pNext->pNext != 0) {
			pNext->pNext->pPrev = 0;
			pNext->pNext = 0;
		}
		pNext->MarkForDestroy();
		pNext = 0;
	}	
	MarkForDestroy();
}

sf::Vector2f CentipedeBody::GetPosition() {
	return Pos;
}
