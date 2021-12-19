#include "behaviourcomponent.h"

namespace golden { namespace ecs {

	BehaviourComponent::BehaviourComponent() : Component("BehaviourComponent") { }
	BehaviourComponent::BehaviourComponent(void(*OnStartFunction)(), void(*OnUpdateFunction)()) : Component("BehaviourComponent")
	{
		this->OnStart = *OnStartFunction;
		this->OnUpdate = *OnUpdateFunction;
	}

	void BehaviourComponent::setOnStartFunction(void(*OnStartFunction)()) { this->OnStart = *OnStartFunction; }
	void BehaviourComponent::setOnUpdateFunction(void(*OnUpdateFunction)()) { this->OnUpdate = *OnUpdateFunction; }

	void BehaviourComponent::InvokeOnStartFunction() const { this->OnStart(); }
	void BehaviourComponent::InvokeOnUpdateFunction() const { this->OnUpdate(); }
}}