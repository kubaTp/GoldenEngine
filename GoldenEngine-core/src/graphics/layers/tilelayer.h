#pragma once

#include "layer.h"
#include "../renderers/batchrenderer2D.h"

namespace golden { namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader& shader, bool uiLayer = false);

			virtual ~TileLayer();
		};

}}
