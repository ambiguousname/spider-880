#include "base_sounds.hpp"
#include "sound.hpp"

void clickSound() {
	static SoundManager::Sound click;
	if (!click.isLoaded()) {
		SoundManager::Load("./assets/click.wav", click);
	}
	click.setPitch(((float)(rand() % 50) + 50)/100);
	click.play();
}

void checkSound() {
	static SoundManager::Sound check;
	if (!check.isLoaded()) {
		SoundManager::Load("./assets/check.wav", check);
	}
	check.play();
}


void errorSound() {
	static SoundManager::Sound error;
	if (!error.isLoaded()) {
		SoundManager::Load("./assets/error.wav", error);
	}
	error.setPitch(((float)(rand() % 50) + 50)/100);
	error.play();
}

void typeSound(float pitch) {
	static SoundManager::Sound type;
	if (!type.isLoaded()) {
		SoundManager::Load("./assets/error.wav", type);
	}
	type.setPitch(pitch);
	type.play();
}