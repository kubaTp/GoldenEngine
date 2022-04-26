#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace golden { namespace graphics {

	class Shader
	{
	public:
		Shader(const char* vertPath, const char* fragPath);
		Shader(std::string vertPath, std::string fragPath);
		Shader(std::string name, std::string vertPath, std::string fragPath);

		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name, float* value, int count);
		void setUniform1i(const GLchar* name, int value);
		void setUniform1iv(const GLchar* name, int* value, int count);
		void setUniform2f(const GLchar* name, const maths::Vec2& vector);
		void setUniform3f(const GLchar* name, const maths::Vec3& vector);
		void setUniform4f(const GLchar* name, const maths::Vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::Mat4& matrix);
		void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

		//abstracts for GL
		void enable() const;
		void disabled() const;

		inline const std::string& getVertPath() const { return m_VertPath; }
		inline const std::string& getFragPath() const { return m_FragPath; }
		inline const std::string& getName() const { return m_Name; }

	private:
		GLuint load();
		GLuint getUniformLocation(const GLchar* name);
		void setTextureIDs();

	private:
		uint32_t m_ShaderID;
		std::string m_VertPath, m_FragPath;
		std::string m_Name;
	};
}}