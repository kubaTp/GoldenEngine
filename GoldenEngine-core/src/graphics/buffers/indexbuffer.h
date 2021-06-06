#pragma once

#include <GL/glew.h>

namespace golden {
	namespace graphics {
		class IndexBuffer
		{
		private:
			unsigned int m_BufferID;
			unsigned int m_Count; //count of indicies

		public:
			IndexBuffer(GLuint* data, GLsizei count);
			IndexBuffer(GLushort* data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline unsigned int getCount() const { return m_Count; }
		};
	}
}