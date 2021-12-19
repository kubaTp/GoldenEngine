#pragma once

#include <vector>
#include <irrKlang.h>

#include "sound.h"

namespace golden { namespace sound {

	static class SoundManager
	{
	public:
		static Sound* get(std::string soundname);
		static Sound* get(std::string soundname, bool loop);
		static float getVolume();

		static void add(Sound* sound);
		static void play(std::string soundName);
		static void changeVolume(float newVolume);
		static void muteAudio();
		static void ummuteAudio();
		static void remove(std::string soundName);
		static void clear();
		static void destroy();
		static void stopAllSounds();

	private:
		static irrklang::ISoundEngine* sound_engine;
		static std::vector<Sound*> m_Sounds;

		static bool m_Mute;
	};
}}