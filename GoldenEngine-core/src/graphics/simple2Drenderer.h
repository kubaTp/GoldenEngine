#pragma once

#include <deque>

#include "renderer2D.h"
#include "staticsprite.h"

namespace golden { namespace graphics {

		class Simple2DRenderer : Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
}}