#include "base_sounds.h"
#include "sound.h"

void clickSound() {
	static SoundManager::Sound click;
	if (!click.isLoaded()) {
		SoundManager::Load("./assets/click.wav", click);
	}
	click.setPitch(((float)(rand() % 50) + 50)/100);
	click.play();
}


void errorSound() {
	static SoundManager::Sound error;
	if (!error.isLoaded()) {
		SoundManager::Load("./assets/error.wav", error);
	}
	error.play();
}