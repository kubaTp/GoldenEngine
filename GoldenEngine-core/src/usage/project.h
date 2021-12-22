#pragma once
#include <string>

namespace golden { namespace usage {

	// class which describes all project
	class Project
	{
	public:
		Project();
		Project(std::string name);

		void changeProjectName(std::string newName) const;

	private:
		std::string m_Name;
	};
}}