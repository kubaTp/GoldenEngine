#include "sound.h"

namespace golden {
	namespace sound {

		Sound::Sound(std::string soundName, std::string soundPath)
			: m_SoundName(soundName), m_SoundPath(soundPath), m_Loop(false) { }

		Sound::Sound(std::string soundName, std::string soundPath, bool loop)
			: m_SoundName(soundName), m_SoundPath(soundPath), m_Loop(loop) {}

		void Sound::change(Sound* sound) 
		{
			this->m_SoundName = sound->m_SoundName;
			this->m_SoundPath = sound->m_SoundPath;
			this->m_Loop = sound->m_Loop;
		}
	}
}