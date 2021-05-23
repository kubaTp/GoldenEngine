#pragma once

#include <GL/glew.h>
#include <vector>
#include "../maths/maths.h"

namespace golden { namespace graphics {

	class Renderable2D;

	class Renderer2D
	{
	protected:
		std::vector<maths::Mat4> m_TransformationStack;
		const maths::Mat4* m_TransformationStackBack;

	protected:
		Renderer2D() { m_TransformationStack.push_back(maths::Mat4::idenity()); m_TransformationStackBack = &m_TransformationStack.back(); }
		 
	public:
		void push(const maths::Mat4& matrix, bool override = false)
		{
			if(override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
			
			m_TransformationStackBack = &m_TransformationStack.back();
		}

		void pop()
		{
			//ADD TO LOG SYSTEM : STATE OF TRANSFORMATION STACK
			if(m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();

			m_TransformationStackBack = &m_TransformationStack.back();
		}

		virtual void begin() {}
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void flush() = 0;
		virtual void end() {}
	};
}}