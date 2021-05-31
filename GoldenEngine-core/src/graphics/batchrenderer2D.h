#pragma once

#include <cstddef>

#include "renderer2D.h"
#include "buffers/indexbuffer.h"

#include "renderable2D.h"

namespace golden { namespace graphics {

#define RENDERER_MAX_SPRITES	60000 //limit of renderer sprites
#define RENDERER_VERTEX_SIZE	sizeof(VertexData) //it grows with members of POD called VertexData
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4 //size of vertex times 4 bc of rectangles and squares
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES //size of buffer given to GPU
#define RENDERER_INDICIES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

	class BatchRenderer2D : public Renderer2D
	{
	private:
		IndexBuffer* m_IBO;

		GLsizei m_IndexCount; //counter to know how many sprites need to be draw, put in vertiecies count
		GLuint m_VBO; //is going to be main buffer which contains all of data, 60k, EBO -> everything buffer object
		GLuint m_VAO;

		VertexData* m_Buffer;
		std::vector<GLuint> m_TextureSlots;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin() override; // bind buffers
		void submit(const Renderable2D* renderable) override; // submit data to buffer
		void flush() override; // draw elements
		void end() override; // unbind buffers

	private:
		void init(); // big function called in conctructor
	};
}}