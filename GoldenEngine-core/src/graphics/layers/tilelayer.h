#pragma once

#include "layer.h"
#include "../renderers/batchrenderer2D.h"
#include "../../maths/mat4.h"

namespace golden { namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader& shader, bool uiLayer = false);
			TileLayer(Shader& shader, maths::Mat4& projectionMatrix, bool uiLayer = false);

			virtual ~TileLayer();
		};

}}
