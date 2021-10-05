#include "resourceloader.h"

std::string golden::ResourceLoader::m_ResPath = "empty path";

namespace golden {

	void ResourceLoader::setResourcePath(std::string respaths)
	{
		m_ResPath = respaths;
	}
	
	std::string ResourceLoader::findFile(std::string filepath)
	{
		return m_ResPath + filepath;
	}
}