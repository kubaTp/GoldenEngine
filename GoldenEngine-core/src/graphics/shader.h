#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace golden { namespace graphics {

	class Shader
	{
	private:
		const char *m_VertPath, *m_FragPath;

	public:
		GLuint m_ShaderID;
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
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
	};
}}