#pragma once

#include <GL/glew.h>

namespace golden { namespace graphics {
	
	class IndexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_Count; //how many vec2 are there for example

	public:
		IndexBuffer(GLushort* data, GLsizei count);

		void bind() const;
		void unbind() const;

		inline GLuint getCount() const { return m_Count; }
	};
}}