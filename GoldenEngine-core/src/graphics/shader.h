#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace golden { namespace graphics {

	class Shader
	{
	public:
		Shader(const char* vertPath, const char* fragPath);
		Shader(std::string vertPath, std::string fragPath);

		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name, float* value, int count);
		void setUniform1i(const GLchar* name, int value);
		void setUniform1iv(const GLchar* name, int* value, int count);
		void setUniform2f(const GLchar* name, const maths::Vec2& vector);
		void setUniform3f(const GLchar* name, const maths::Vec3& vector);
		void setUniform4f(const GLchar* name, const maths::Vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::Mat4& matrix);

		//abstracts for GL
		void enable() const;
		void disabled() const;

	private:
		GLuint load();
		GLuint getUniformLocation(const GLchar* name);

	private:
		uint32_t m_ShaderID;
		const char* m_VertPath, * m_FragPath;
	};
}}