#pragma once
#include "src/components/components_pack.h"
#include "src/core.h"

using namespace golden;
using namespace graphics;

class MyComponent : public golden::ecs::Component
{
	void OnStart() override
	{
		lg::logInfo("ON START");

		golden::sound::SoundManager::changeVolume(0.3f);
		golden::sound::SoundManager::play("menu");
	}

	void OnUpdate() override
	{		
		if (usage::Input::isKeyPressed(GLFW_KEY_1))
			lg::logInfo("1 key is pressed in mycomponent.h");
	}
};