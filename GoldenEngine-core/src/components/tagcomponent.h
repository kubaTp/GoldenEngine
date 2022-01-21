#pragma once

#include "component.h"

namespace golden { namespace ecs {

	class TagComponent : public Component
	{
	public:
		TagComponent() { compType = ComponentsType::TAG_COMPONENT; }

	public:
		bool compareTags(std::string& othertags)
		{
			if (othertags == tag)
			{
				return true;
			}

			return false;
		}

	public:
		std::string tag = "untaged";
	};
}}