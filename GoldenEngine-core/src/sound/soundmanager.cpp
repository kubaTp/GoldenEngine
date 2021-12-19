#include "soundmanager.h"

namespace golden { namespace sound {

	irrklang::ISoundEngine* SoundManager::sound_engine = irrklang::createIrrKlangDevice();
	std::vector<Sound*> SoundManager::m_Sounds;
	bool SoundManager::m_Mute = false;

	void SoundManager::add(Sound* sound) { m_Sounds.push_back(sound); }

	Sound* SoundManager::get(std::string soundname)
	{
		for (Sound* sound : m_Sounds)
		{
			if (sound->getSoundName() == soundname)
				return sound;
		}

		// TODO : make default music ?
		return nullptr;
	}

	Sound* SoundManager::get(std::string soundname, bool loop)
	{
		for (Sound* sound : m_Sounds)
		{
			if (sound->getSoundName() == soundname)
			{
				if (sound->getLoop() == loop)
					return sound;
			}
		}

		return nullptr;
	}

	float SoundManager::getVolume()
	{
		return sound_engine->getSoundVolume();
	}

	void SoundManager::play(std::string soundName)
	{
		const Sound& sound = *get(soundName);
		sound_engine->play2D(sound.getSoundPath().c_str(), false);
	}

	void SoundManager::changeVolume(float newVolume)
	{
		if(!m_Mute) sound_engine->setSoundVolume(newVolume);
	}

	void SoundManager::muteAudio() 
	{
		m_Mute = true;
		sound_engine->setSoundVolume(0);
	}

	void SoundManager::ummuteAudio()
	{
		m_Mute = true;
	}

	void SoundManager::remove(std::string soundName)
	{
		for (uint16_t i = 0; i < m_Sounds.size(); i++)
		{
			if (m_Sounds[i]->getSoundName() == soundName)
			{
				m_Sounds.erase(m_Sounds.begin() + i);
			}
		}
	}

	void SoundManager::clear() { m_Sounds.clear(); }
	void SoundManager::destroy() { sound_engine->drop(); }
	void SoundManager::stopAllSounds() { sound_engine->stopAllSounds(); }
}}