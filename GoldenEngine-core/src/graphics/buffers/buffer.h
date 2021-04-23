#pragma once

#include <GL/glew.h>

namespace golden { namespace graphics {
	

	class Buffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount; //how many vec2 are there for example

	public:
		Buffer(GLfloat* data, GLsizei count,  GLuint compoenentCount);

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_ComponentCount; }
	};
}}