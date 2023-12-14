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
		void setPitch(float pitch);
		bool isLoaded() {
			return loaded;
		}
	};

	void Initialize();

	bool Load(const char* path, Sound& out);

	void Uninitialize();
};