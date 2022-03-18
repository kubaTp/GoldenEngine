#include "resourceloader.h"

std::string golden::ResourceLoader::m_ResPath = "empty path";
std::string golden::ResourceLoader::m_PrjPath = "empty path";

namespace golden {
	
	void ResourceLoader::setResourcePath(std::string respaths)
	{
		m_ResPath = respaths;
	}
	
	void ResourceLoader::setProjectPath(std::string prjpath)
	{
		m_PrjPath = prjpath;
	}

	std::string ResourceLoader::findFile(std::string filepath)
	{
		return m_ResPath + filepath;
	}
}