#pragma once

#include <string>
#include <iostream>

#include <filesystem>

namespace golden {

	class ResourceLoader
	{
	private:
		ResourceLoader() {}

	public:
		static void setResourcePath(std::string respaths);
		static void setProjectPath(std::string prjpath);

		static std::string getResourcePath() { return m_ResPath; }
		static std::string getResourcePath_abs() { return absPath(m_ResPath); }
		static std::string getProjectPath() { return m_PrjPath; }
		static std::string getSerializedDataPath();
		static std::string getCWD() { return std::filesystem::current_path().u8string(); }

		static std::string findFile(std::string filepath);	
		
	private:
		static std::string absPath(std::string& path)
		{
			std::string result = path;
			std::replace(result.begin(), result.end(), '/', '\\');

			return result;
		}

		static std::string m_ResPath;
		static std::string m_PrjPath;
	};
}