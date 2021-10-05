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
		static std::string getResourcePath() { return m_ResPath; }
		static std::string getResourcePath_abs() { return absPath(m_ResPath); }

		static std::string findFile(std::string filepath);	
		static std::string getCWD() { return std::filesystem::current_path().u8string(); }

	private:
		static std::string absPath(std::string& path)
		{
			std::string result = path;
			std::replace(result.begin(), result.end(), '/', '\\');

			return result;
		}

		static std::string m_ResPath;
	};
}