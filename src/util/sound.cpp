#include "sound.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

using namespace SoundManager;

ma_engine engine;

void SoundManager::Initialize() {
	ma_result result;
	
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		std::cerr << "Could not initialize audio engine." << std::endl;
	}
}

bool SoundManager::Load(const char* path, Sound& out) {
	ma_result result = ma_sound_init_from_file(&engine, path, 0, NULL, NULL, &out.sound);

	if (result != MA_SUCCESS) {
		std::cerr << "Could not load sound " << path << ": " << result << std::endl;
		out.loaded = false;
		return false;
	}

	out.loaded = true;
	return true;
}

void SoundManager::Uninitialize() {
	ma_engine_uninit(&engine);
}

void Sound::play() {
	ma_sound_start(&sound);
}

void Sound::stop() {
	ma_sound_stop(&sound);
}

void Sound::setPitch(float pitch) {
	ma_sound_set_pitch(&sound, pitch);
}

void Sound::setLoop(bool shouldLoop) {
	ma_sound_set_looping(&sound, shouldLoop);
}

void Sound::awaitPlay() {
	while (ma_sound_is_playing(&sound)) {
		continue;
	}
}