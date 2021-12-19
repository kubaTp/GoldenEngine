#pragma once
#include <string>
#include <iostream>

namespace golden { class Chief; namespace ecs {
	
	class Component 
	{
	public:
		inline const std::string& getName() const { return m_Name; }

		virtual void setOnStartFunction(void(*OnStartFunction)()) { }
		virtual void setOnUpdateFunction(void(*OnUpdateFunction)()) { }

	private:
		virtual void InvokeOnStartFunction() const { }
		virtual void InvokeOnUpdateFunction() const { }

		friend class Chief;

	public:
		Component(std::string name) { m_Name = name;  }

	public:
		Component() { }

	private:
		std::string m_Name;
	};
}}