#pragma once

#include <GL/glew.h>

namespace golden { namespace graphics {
	

	class Buffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount; //vec2 = 2 || 2 * vec2 = 4

	public:
		Buffer(GLfloat* data, GLsizei count,  GLuint compoenentCount);

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_ComponentCount; }
	};
}}