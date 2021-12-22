#pragma once
#include "../utils/logger.h"
#include "../utils/resourceloader.h"

#include <fstream>
#include <sstream>

#define CPP_WAY_READING_FILES

namespace golden {

	class FileManager
	{
	private:
		FileManager() { }

	public:
		inline static std::string read_file(const char* filepath)
		{
			// CPP IS ACTIVE

			// better for smaller files | < mb
			#pragma region C_WAY_OF_READING_FILES
#ifdef C_WAY_READING_FILES
			FILE* file = fopen(filepath, "rt"); //rt => read text file
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length];
			memset(data, 0, length);

			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);

			fclose(file);

			std::string result(data);
			delete[] data;

			return result;
#endif
#pragma endregion

			// better for bigger files | > mb
			#pragma region CPP_WAY_OF_READING_FILES
#ifdef CPP_WAY_READING_FILES
			std::ifstream in(filepath);

			if (in)
			{
				std::string content;
				in.seekg(0, std::ios::end);
				content.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&content[0], content.size()); // save spaces for termination mark 
				in.close();

				return content;
			}
#endif
#pragma endregion

			//std::cout << "path : " << filepath << std::endl;
			//throw std::runtime_error("Golden Engine 'read_file()' error: failed to read a file!"); // TODO : change this to logger logError

			std::stringstream ss;
			ss << "file at path " << filepath << " could be read";
			Logger::logWarning(ss.str());
		}

		inline static void create_dir(std::string directoryname) // create dir in project location
		{
			std::string path(ResourceLoader::getProjectPath() + directoryname);

			if (directoryname.find("/") != std::string::npos)
				std::filesystem::create_directories(path);
			else
				std::filesystem::create_directory(path);
		}
	};
}