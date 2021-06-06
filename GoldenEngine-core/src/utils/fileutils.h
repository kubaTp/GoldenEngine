#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

#define CPP_WAY_READING_FILES

namespace golden {

	inline std::string read_file(const char* filepath)
	{
		// NOW CPP IS ACTIVE
		
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

		throw std::runtime_error("Golden Engine 'read_file()' error: failed to read a file!");
	}
}