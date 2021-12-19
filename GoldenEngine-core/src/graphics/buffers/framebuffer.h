#pragma once
#include "../../base.h"
#include "../../gebase.h"

#include <GL/glew.h>

namespace golden { namespace graphics {

	struct FramebufferSpecification 
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
	};

	class Framebuffer 
	{
	public:
		Framebuffer(const FramebufferSpecification& spec);
		~Framebuffer();
		
		void Invalidate();

		void Bind();
		void Unbind();

		const FramebufferSpecification& getSpecification() { return m_Specification; }
		const uint32_t& getColorAttachment() { return m_ColorAttachment; }
		const uint32_t& getBuffer() { return m_BufferID; }

	private:
		uint32_t m_BufferID; // framebuffer
		uint32_t m_ColorAttachment, m_Depthattachment; // TODO : make this customizable in the future
		FramebufferSpecification m_Specification;
	};

}}