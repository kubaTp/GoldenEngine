#pragma once
#include <string>
#include <iostream>

namespace golden { class Chief; namespace ecs {
	
	class Component 
	{
	public:
		virtual inline const std::string getName() const { return m_Name; }

		virtual void setOnStartFunction(void(*OnStartFunction)()) { }
		virtual void setOnUpdateFunction(void(*OnUpdateFunction)()) { }

	private:
		virtual void InvokeOnStartFunction() const { }
		virtual void InvokeOnUpdateFunction() const { }

		friend class Chief;

	public:
		Component(std::string name) { m_Name = name; }
		Component() { }

	protected:
		std::string m_Name;
	};
}}