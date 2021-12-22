#pragma once

#include "component.h"

// component with onStart and onUpdate functions

namespace golden { namespace ecs {

	class BehaviourComponent : public Component {

	public:
		BehaviourComponent();
		BehaviourComponent(void(*OnStartFunction)(), void(*OnUpdateFunction)());

	private:
		typedef void(*StartFunction)();
		typedef void(*UpdateFunction)();

		static void defaultFunction() { }

		StartFunction OnStart = &defaultFunction;
		UpdateFunction OnUpdate = &defaultFunction;

		void setOnStartFunction(void(*OnStartFunction)()) override;
		void setOnUpdateFunction(void(*OnUpdateFunction)()) override;

		void InvokeOnStartFunction() const override;
		void InvokeOnUpdateFunction() const override;
	};
}}