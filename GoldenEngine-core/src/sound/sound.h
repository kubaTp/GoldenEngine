#pragma once

#include <string>
#include <iostream>

namespace golden { namespace sound {

	class Sound
	{
	public:
		Sound(std::string soundName, std::string soundPath);
		Sound(std::string soundName, std::string soundPath, bool loop);

		void change(Sound* sound);

		const std::string& getSoundName() const { return m_SoundName; }
		const std::string& getSoundPath() const { return m_SoundPath; }
		const bool& getLoop() const { return m_Loop; }

		inline virtual void debug()
		{
			std::cout << "soundname: " << m_SoundName <<
				", soundpath: " << m_SoundPath << ", loop: " << m_Loop << std::endl;
		}

	private:
		std::string m_SoundName, m_SoundPath;
		bool m_Loop;
	};
}}