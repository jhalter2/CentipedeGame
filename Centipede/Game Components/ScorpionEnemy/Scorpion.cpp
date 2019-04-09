#include "Scorpion.h"
#include "Mushroom.h"
#include "PoisonMushroom.h"
#include "Bullet.h"
#include "Ship.h"
#include "MushroomField.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "ExplosionFactory.h"
#include "ScorpionManager.h"

Scorpion::Scorpion() {
	bitmap = &ResourceManager::GetTextureBitmap("Scorpion");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Scorpion"), 4, 1);
	MainSprite.setOrigin((float)(MainSprite.getTextureRect().width / 2), (float)(MainSprite.getTextureRect().height));

	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::ScorpionKilled);

	SetCollider(MainSprite, *bitmap);
}

void Scorpion::Initialize(MushroomField* pF, sf::Vector2f pos, float speed, float direction) {
	this->Pos = pos;
	this->speed = speed;
	MainSprite.setScale(direction, 1);
	steps = 0;
	AniState = 0;
	pM = pF;

	MainSprite.setPosition(Pos);
	//the continuous sound, set to loop
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::ScorpionSound));

	RegisterCollision<Scorpion>(*this);
}

void Scorpion::Update() {
	MainSprite.Update();
	Pos.x += speed;
	steps++;
	if (steps >= 16) ChangeAni();
	MainSprite.setPosition(Pos);
	if (Pos.x > WindowManager::MainWindow.getSize().x + cell_size) {
		ScorpionManager::ScorpionDied();
		SoundManager::StopScorpionSnd();
		MarkForDestroy();
	}

	if (Pos.x < 0 - cell_size) {
		ScorpionManager::ScorpionDied();
		SoundManager::StopScorpionSnd();
		MarkForDestroy();
	}
}

void Scorpion::Draw() {
	WindowManager::MainWindow.draw(MainSprite);
}

void Scorpion::Destroy() {
	DeregisterCollision<Scorpion>(*this);
}

void Scorpion::Collision(Bullet *other) {
	Die();
}

void Scorpion::Collision(Mushroom *other) {
	pM->ConvertToPoison(other);
}

void Scorpion::ChangeAni() {
	MainSprite.SetAnimation(AniState, AniState, false, false);
	if (AniState == 3) AniState = 1;
	else AniState++;
	steps = 0;
}

void Scorpion::Die() {
	ScoreManager::SendScoreCmd(pDeath);
	SoundManager::StopScorpionSnd();
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
	ExplosionFactory::CreateExplosion(Pos);
	ScorpionManager::ScorpionDied();
	MarkForDestroy();
}

void Scorpion::FieldClear() {
	SoundManager::StopScorpionSnd();
	ScorpionManager::ScorpionDied();
	MarkForDestroy();
}
