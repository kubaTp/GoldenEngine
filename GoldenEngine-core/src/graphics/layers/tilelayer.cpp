#include "tilelayer.h"

namespace golden { namespace graphics {

#if 1
		TileLayer::TileLayer(Shader& shader, bool uiLayer) :
			Layer(shader, maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 1.0f, -1.0f), uiLayer) { }
#else
	TileLayer::TileLayer(Shader& shader) :
		Layer(shader, maths::Mat4::perspective(90.0f, 960.0f / 540.0f, 1.0f, -1.0f)) { }
#endif

		TileLayer::~TileLayer() { }
}}