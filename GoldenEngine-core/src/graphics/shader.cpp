#include "shader.h"
#include <glm/glm.hpp>

namespace golden { namespace graphics {

	Shader::Shader(const char* vertPath, const char* fragPath) : m_VertPath(vertPath), m_FragPath(fragPath), m_Name("empty") 
	{
		m_ShaderID = load();
		setTextureIDs();
	}
	Shader::Shader(std::string vertPath, std::string fragPath) : m_VertPath(vertPath), m_FragPath(fragPath), m_Name("empty") 
	{ 
		m_ShaderID = load();
		setTextureIDs();
	}
	Shader::Shader(std::string name, std::string vertPath, std::string fragPath) : m_VertPath(vertPath), m_FragPath(fragPath), m_Name(name) 
	{ 
		m_ShaderID = load();
		setTextureIDs();
	}

	Shader::~Shader() { glDeleteProgram(m_ShaderID); }

	GLuint Shader::load()
	{
		GLuint program  = glCreateProgram();
		GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = FileManager::read_file(m_VertPath.c_str());
		std::string fragSourceString = FileManager::read_file(m_FragPath.c_str());

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		//vertex
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compilied vertex shader: " << std::endl << &error[0] << std::endl; // log this one
			glDeleteShader(vertex);

			return 0;
		}

		//fragment
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compilied fragment shader: " << std::endl << &error[0] << std::endl; // log this one
			glDeleteShader(fragment);

			return 0;
		}

		glAttachShader(program, vertex); //attach shaders to program
		glAttachShader(program, fragment);

		glLinkProgram(program); //create executables of shaders
		glValidateProgram(program); //check executables to contain this in program's logs

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar* name, float* value, int count)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1iv(const GLchar* name, int* value, int count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform2f(const GLchar* name, const maths::Vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* name, const maths::Vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const maths::Vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const maths::Mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::disabled() const
	{
		glUseProgram(0);
	}

	GLuint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::setTextureIDs()
	{
		GLint textIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		enable();
		setUniform1iv("textures", textIDs, 10);
		disabled();
	}
}}