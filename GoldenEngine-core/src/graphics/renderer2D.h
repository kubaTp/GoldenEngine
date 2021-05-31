#pragma once

#include <GL/glew.h>
#include <vector>
#include "../maths/maths.h"

namespace golden { namespace graphics {

	class Renderable2D;

	class Renderer2D
	{
	protected:
		std::vector<maths::Mat4> m_TransformationStack; // vector of mat4, group can add special mat4 to change position of everyone sprite in the group
		const maths::Mat4* m_TransformationStackBack; // represents the last on mat4 in the m_TransformationStack

	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(maths::Mat4::idenity());  // push neutral mat4 to the end
			m_TransformationStackBack = &m_TransformationStack.back(); // assign the last of mat4 to the m_TransformationStackBack
		}
		 
	public:
		void push(const maths::Mat4& matrix, bool override = false)
		{
			if(override) // if the last one of mat4 needs to be overriden
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix); // push new matrix on the end which is multiplied by last one of the m_TransformationStack
			
			m_TransformationStackBack = &m_TransformationStack.back();  // assign the last of mat4 to the m_TransformationStackBack
		}

		void pop()
		{
			//ADD TO LOG SYSTEM : STATE OF TRANSFORMATION STACK
			if(m_TransformationStack.size() > 1) // if the size is greater than 1
				m_TransformationStack.pop_back(); // deletes the last one of mat4 in m_TransformationStackBack

			m_TransformationStackBack = &m_TransformationStack.back(); // assign the last of mat4 to the m_TransformationStackBack
		}

		virtual void begin() {} // asssign all buffers
		virtual void submit(const Renderable2D* renderable) = 0; // submit sprite to the renderer
		virtual void flush() = 0; // drawcall
		virtual void end() {} // unbind all buffers
	};
}}