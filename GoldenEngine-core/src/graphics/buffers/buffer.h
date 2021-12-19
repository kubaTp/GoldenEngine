#pragma once

#include <GL/glew.h>

namespace golden { namespace graphics {

	class Buffer
	{
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint compoenentCount);
		~Buffer();

		void bind() const;
		void unbind() const;

		inline unsigned int getComponentCount() const { return m_ComponentCount; }

	private:
		unsigned int m_BufferID;
		unsigned int m_ComponentCount; //vec2 = 2 || 2 * vec2 = 4
	};
}}