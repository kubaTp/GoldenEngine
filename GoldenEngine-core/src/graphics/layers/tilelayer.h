#pragma once

#include "layer.h"
#include "../batchrenderer2D.h"

namespace golden { namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader& shader);
			virtual ~TileLayer();
		};

}}
