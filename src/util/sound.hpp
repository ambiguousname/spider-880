#pragma once

#include <iostream>
#include "miniaudio.h"

namespace SoundManager {
	class Sound {
		protected:
		ma_sound sound;
		bool loaded = false;

		public:
		friend bool Load(const char* path, Sound& out);

		void play();
		void stop();
		void setPitch(float pitch);
		void setLoop(bool shouldLoop);
		bool isLoaded() {
			return loaded;
		}

		void awaitPlay();

		~Sound();
	};

	void Initialize();

	bool Load(const char* path, Sound& out);

	void Uninitialize();
};