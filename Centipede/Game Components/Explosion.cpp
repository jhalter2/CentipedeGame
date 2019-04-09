#include "Explosion.h"
#include "SoundManager.h"

Explosion::Explosion() {
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Explosion"), 4, 2);
	MainSprite.setOrigin((float)(MainSprite.getTextureRect().width / 2), (float)(MainSprite.getTextureRect().height / 2));
	MainSprite.setScale(0.5f, 0.5f);
}

void Explosion::Initialize(sf::Vector2f pos) {
	AniState = 0;
	this->Position = pos;
	MainSprite.setPosition(pos);
	SoundManager::SendSoundCmd(SoundManager::GetSoundCommand(SoundManager::SoundEvents::CritterDeathSound));
}

void Explosion::Update() {
	ChangeAni();
}

void Explosion::Draw() {
	WindowManager::MainWindow.draw(MainSprite);
}

void Explosion::ChangeAni() {
	MainSprite.SetAnimation(AniState, AniState, false, false);
	if (AniState == 7) MarkForDestroy();
	else AniState++;
}