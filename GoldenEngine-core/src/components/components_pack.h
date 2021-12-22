#pragma once

/*--- ALL COMPONENTS ---*/
#include "component.h"
#include "behaviourcomponent.h"

#include "../../extLibs/json_struct/json_struct.h"
namespace golden { namespace ecs {

	struct ComponentSpec
	{
		std::string name;
		ComponentSpec() : name("empty") { }

		golden::ecs::Component& convertToComponent() const // returns reference to new component
		{
			golden::ecs::Component* newComp;
			if (name == "BehaviourComponent")
				newComp = new golden::ecs::BehaviourComponent();
			return *newComp;
		}

		JS_OBJECT(JS_MEMBER_WITH_NAME(name, "name"));
	};
}}