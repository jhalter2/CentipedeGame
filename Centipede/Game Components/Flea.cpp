#include "Flea.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "Ship.h"
#include "MushroomField.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "ExplosionFactory.h"
#include "MushroomFactory.h"
#include "FleaManager.h"

Flea::Flea(MushroomField* pF) {
	bitmap = &ResourceManager::GetTextureBitmap("Flea");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Flea"), 2, 2);

	MainSprite.setOrigin((float)(MainSprite.getTextureRect().width / 2), (float)(MainSprite.getTextureRect().height / 2));
	MainSprite.setScale(1.0f, 1.0f);

	SetCollider(MainSprite, *bitmap);
}

void Flea::Initialize(sf::Vector2f p, MushroomField* pF) {
	Pos = p;
	pM = pF;
	health = 2;
	CanSpawn = true;
	steps = 0;
	speed = 2;
	AniState = 0;
	row = 0.0f;
	col = Pos.x / cell_size;
	MainSprite.setPosition(Pos);
	//the continuous sound, set to loop
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::FleaSound));

	RegisterCollision<Flea>(*this);
}

void Flea::Update() {
	MainSprite.Update();
	Pos.y += (float)speed;
	steps += speed;
	if (Pos.y > WindowManager::MainWindow.getSize().y) {
		SoundManager::StopFleaSnd();
		FleaManager::FleaDied();
		MarkForDestroy();
	}

	if (steps >= 16) {
		ChangeAniState();
		if (CanSpawn) SpawnMushroom();
		steps = 0;
		row += 1.0f;
	}

	MainSprite.setPosition(Pos);
}

void Flea::Draw() {
	WindowManager::MainWindow.draw(MainSprite);
}

void Flea::Destroy() {
	DeregisterCollision<Flea>(*this);
}

//check if a mushroom is ahead and if not then possibly spawn one
void Flea::SpawnMushroom() {
	if (pM->FleaCheck(row, col)) {
		rand1 = rand() % 100 + 1;
		if (rand1 < 50) {
			pM->SpawnOneShroom(sf::Vector2f(Pos.x, Pos.y));
		}
	}
}

void Flea::ChangeAniState() {
	MainSprite.SetAnimation(AniState, AniState, false, false);
	if (AniState == 3) AniState = 1;
	else AniState++;
}

void Flea::Collision(Bullet *other) {
	Die();
}

void Flea::Collision(Ship *other) {
	ExplosionFactory::CreateExplosion(Pos);
	SoundManager::StopFleaSnd();
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
	MarkForDestroy();
}

void Flea::Die() {
	if (health <= 0) {
		ScoreManager::AddScore(200);
		ExplosionFactory::CreateExplosion(Pos);
		SoundManager::StopFleaSnd();
		SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
		FleaManager::FleaDied();
		MarkForDestroy();
	}
	else {
		health--;
		CanSpawn = false;
		speed = 4;
	}
}

void Flea::FieldClear() {
	SoundManager::StopFleaSnd();
	FleaManager::FleaDied();
	MarkForDestroy();
}