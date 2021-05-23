#pragma once

#include <GL/glew.h>

namespace golden { namespace graphics {
	
	class IndexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_Count; //count of indicies

	public:
		IndexBuffer(GLuint* data, GLsizei count);
		IndexBuffer(GLushort* data, GLsizei count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline GLuint getCount() const { return m_Count; }
	};

}}