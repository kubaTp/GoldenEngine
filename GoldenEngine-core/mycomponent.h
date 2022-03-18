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
	}

	void OnUpdate() override
	{		
		if (usage::Input::isKeyPressed(GLFW_KEY_W))
			lg::logInfo("is key pressed in mycomponent.h");

	}
};