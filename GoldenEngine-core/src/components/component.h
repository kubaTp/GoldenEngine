#pragma once

#include "component.h"
#include <iostream>

namespace golden { namespace ecs {

	enum ComponentsType
	{
		OTHER = 0, // created by game designer
		TAG_COMPONENT = 1, // holds tag
		TRANSFORM_COMPONENT = 2, // holds transform
	};

	class Component {

	public:
		Component() { compType = ComponentsType::OTHER; }

	protected:
		virtual void OnStart() { }
		virtual void OnUpdate() { }

	public:
		void InvokeOnStartFunction() { OnStart(); }
		void InvokeOnUpdateFunction() { OnUpdate(); }

	public:
		ComponentsType compType;
	};
}}