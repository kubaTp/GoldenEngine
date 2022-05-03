#define PREDEFINED_MACROS
#include "src/core.h"

#define BATCH_RENDERER 1
#define MAX_SPRITE_AMOUNT 0

#define CHIEF_RENDERING 1

#define GE_EDITOR 0
// projection matrix is maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 1.0f, -1.0f)

#include "mycomponent.h" // example component file

#pragma region SANDBOX
#if 1

int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;
	using namespace sound;

	Timer mainTimer;
	mainTimer.start();

	system("CLS");
	srand(time(NULL));

	rs::setResourcePath("D:/Code/Games Engine/Reference/GoldenEngine-dev/assets/");
	rs::setProjectPath("D:/Code/Games Engine/Reference/GoldenEngine-dev/");

	Scene mainscene("main_scene");

	SoundManager::add(new Sound("guitar",      rs::findFile("music/guitar.wav"), true));
	SoundManager::add(new Sound("barbarian",   rs::findFile("music/barbarian.wav"), true));
	SoundManager::add(new Sound("buttonclick", rs::findFile("music/buttonclick.mp3")));
	SoundManager::add(new Sound("menu",		   rs::findFile("music/menumusic.mp3")));

	Window window("Golden Engine", 1200.0f, 730.0f);
	window.clear();

	// event on resize
	float prMatrixX = maths::precisionRoundedFloat(window.getWidth() / 30.0f); // -> 40.0f
	float prMatrixY = maths::precisionRoundedFloat(window.getHeight() / 34.0f); // -> 22.0f

	maths::Mat4 calculatedPrMatrix = maths::Mat4::orthographic(-prMatrixX / 2, prMatrixX / 2, -prMatrixY / 2, prMatrixY / 2, 1, -1);
	
	Chief::init(new BatchRenderer2D(), &window);

	Shader shader_lighting(rs::findFile("shaders/basic.vert"), rs::findFile("shaders/basic.frag"));
	Shader shader(rs::findFile("shaders/basic.vert"),		   rs::findFile("shaders/font.frag"));
	Shader font_shader(rs::findFile("shaders/basic.vert"),     rs::findFile("shaders/font.frag"));

	shader_lighting.enable();
	shader_lighting.setUniform2f("light_pos", Vec2(0, 0));

	TileLayer uiLayer(font_shader, calculatedPrMatrix, true);
	TileLayer layer(shader, calculatedPrMatrix);
	TileLayer background_layer(shader_lighting, calculatedPrMatrix);

	mainscene.addLayer("bg_layer", &background_layer);
	mainscene.addLayer("layer",    &layer);	
	mainscene.addLayer("uiLayer",  &uiLayer);

	mainscene.removeLayer("adsad"); // validating

	Camera mainCamera("Main Camera", maths::Vec3(0, 0, 0), maths::Vec3(0, 0, 0));
	mainscene.insertCamera(&mainCamera);

	Chief::insertScene(&mainscene);

	Texture textures[] =
	{
		Texture(rs::findFile("img/24Bit_img_2.png")),
		Texture(rs::findFile("img/24Bit_img_chess.png")),
		Texture(rs::findFile("img/player_01.png")),
		Texture(rs::findFile("img/sky.png"))
	};

	#pragma region SPRITE_SUBMITING
#if 0
#if MAX_SPRITE_AMOUNT
	for (float y = -9.0f; y < 9.0f; y += 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += .1f)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::Vec4(1, rand() % 1000 / 1000.0f, 0, 1)));
		}
	}
#else
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::Vec4(1, rand() % 1000 / 1000.0f, 0, 1)));
			layer.add(new Sprite(x, y, 0.9f, 0.9f, &textures[rand() % 3]));
		}
	}

#endif
#endif
	#pragma endregion

	Sprite* sky_bg = new Sprite("background",  -22.0f, -11.0f, 44, 22, &textures[3]);
	background_layer.add(sky_bg);

	Sprite* transparentSprite = new Sprite("player", - 3, -3, 3, 3, &textures[2]);
	layer.add(transparentSprite);
	transparentSprite->getComponent<ecs::TagComponent>()->tag = "player";

	transparentSprite->addComponent<MyComponent>(); // adding component

	if (transparentSprite->hasComponent<ecs::TransformComponent>())
	{
		lg::logInfo("has the component");
		std::shared_ptr<ecs::TransformComponent> transform = transparentSprite->getComponent<ecs::TransformComponent>();	
	}
	else
		lg::logError("transparent sprite does not has the component");

	#pragma region ECS_DEBUGING
#if 0
	std::cout << "player pos : "   << transparentSprite->getComponent<ecs::TransformComponent>()->position << endl;
	std::cout << "player rot : "   << transparentSprite->getComponent<ecs::TransformComponent>()->rotation << endl;
	std::cout << "player scale : " << transparentSprite->getComponent<ecs::TransformComponent>()->scale    << endl;

	std::cout << "background pos : "   << sky_bg->getComponent<ecs::TransformComponent>()->position << endl;
	std::cout << "background rot : "   << sky_bg->getComponent<ecs::TransformComponent>()->rotation << endl;
	std::cout << "background scale : " << sky_bg->getComponent<ecs::TransformComponent>()->scale    << endl;
#endif
#pragma endregion

	FontManager::add(new Font(FontType::Inter_Regular, rs::findFile("fonts/Inter-Regular.ttf"), 60));

	//FontManager::add(new Font(FontType::Jura, rs::findFile("fonts/Jura.ttf"), 50));
	//FontManager::add(new Font(FontType::SourceSerifPro , rs::findFile("fonts/SourceSerifPro-Regular.ttf"), 50));

	Label* fpsLabel  = new Label("fps: 0", -20.0f, 10.0f, FontType::Inter_Regular, 0xffffffff);
	Label* nameLabel = new Label("Project: Sandbox", -15.0f, 10.0f, FontType::Inter_Regular, 0xffffffff);

	uiLayer.add(fpsLabel);
	uiLayer.add(nameLabel);
	
	double x, y;
	Mat4 rotationMatrix = Mat4::idenity();

	float deltaTime = 0.0f;

	#pragma region SERIALIZATION_TEST

	SerializationService::serializeScene(&mainscene);
	//if (SerializationService::deserializeScene("main_scene"))
		//lg::logInfo("Serialization is ok!");

	#pragma endregion

	SoundManager::muteAudio();

	Chief::check();

	/*--- GAME LOOP ---*/
	while (Chief::appRunning())
	{
		Chief::clear();

		#pragma region GE_EDITOR_LAYER
		#if GE_EDITOR
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();


				ImGui::Begin("Function panel");
				ImGui::Text("Project Sanbox");
				ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);

				ImGui::Image((void*)Chief::framebuffer->getBuffer(), ImVec2{ 320 * 1.5f, 180.0f * 1.5f });
				ImGui::End();
		#endif
#pragma endregion

		//rotationMatrix = Mat4::rotation(40, Vec3(0, 0, 1));
		//rotationMatrix = Mat4::translation(Vec3(4.0f, 0.0f, 0.0f));
		
		//shader.enable();
		//shader.setUniformMat4("ml_matrix", rotationMatrix);
		//shader.disabled();

		#pragma region COLOR_CHANGING
#if 0
		std::vector<Renderable2D*> res = layer.getRenderables();
		for (Renderable2D* rs : res)
		{
			float color = (sin(deltaTime) / 2 + 0.5f);
			rs->setColor(Vec4(color, 1, 1, 1));
		}
#endif
		#pragma endregion

		usage::Input::getMousePosition(x, y);
		shader_lighting.enable();
		shader_lighting.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		shader_lighting.disabled();

		transparentSprite->getComponent<ecs::TransformComponent>()->position = 
			maths::Vec3(usage::Input::getKeyboardInput(usage::InputKind::Horizontal), usage::Input::getKeyboardInput(usage::InputKind::Vertical), 0);

		//mainCamera.position = maths::Vec3(usage::Input::getKeyboardInput(usage::InputKind::Horizontal), usage::Input::getKeyboardInput(usage::InputKind::Vertical), 0);

		fpsLabel->content = ("fps: " + std::to_string(window.fps));
		
		#pragma region INPUT_TESTING
#if 1
		if (usage::Input::isMouseButtonPressedDown(GLFW_MOUSE_BUTTON_1))
			Logger::logInfo("mouse 1 button is down");

		//if (window.isMouseButtonDown(GLFW_MOUSE_BUTTON_1))
			//std::cout << "mouse button works 2 times per frame" << endl;

		if (usage::Input::isKeyPressedDown(GLFW_KEY_W) || usage::Input::isKeyPressedDown(GLFW_KEY_S) || usage::Input::isKeyPressedDown(GLFW_KEY_A) || usage::Input::isKeyPressedDown(GLFW_KEY_D))
			SoundManager::play("buttonclick");

		//if (window.isKeyDown(GLFW_KEY_T))
			//std::cout << "key works 2 times per frame" << endl;
#endif
	#pragma endregion

		Chief::drawScene();

		#pragma region GE_EDITOR_RENDER
#if GE_EDITOR
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
#pragma endregion

		Chief::update();
	}

	SoundManager::destroy();
	return 0;
}

#endif
#pragma endregion

#pragma region 3D
#if 0

#include "src/core.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "extLibs/stb-image/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{
	rs::setResourcePath("D:/Code/Games Engine/Reference/GoldenEngine-dev/assets/");
	rs::setProjectPath("D:/Code/Games Engine/Reference/GoldenEngine-dev/");

	Window window("3d sandbox", 820, 600, true);

	// todo : set up 3drenderable class
	golden::graphics::Shader shaderProgram(rs::findFile("shaders/default.vert"), rs::findFile("shaders/default.frag"));

	uint32_t vao, vbo, ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	golden::graphics::Texture brickTex(rs::findFile("img/24Bit_img_chess_2.png"));

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	while (!window.closed())
	{
		window.clear();

		shaderProgram.enable();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)820 / 600, 0.1f, 100.0f);

		shaderProgram.setUniformMat4("model", model);
		shaderProgram.setUniformMat4("view", view);
		shaderProgram.setUniformMat4("proj", proj);

		shaderProgram.setUniform1f("scale", 0.5f);

		brickTex.bind();

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		window.update();
	}

	return 0;
}
#endif
#pragma endregion

#pragma region FREETYPE_TEST
#if 0
#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "extLibs/stb-image/stb_image_write.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#define NUM_GLYPHS 128

#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "extLibs/stb-image/stb_image_write.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#define NUM_GLYPHS 128

struct glyph_info {
	int x0, y0, x1, y1;	// coords of glyph in the texture atlas
	int x_off, y_off;   // left & top bearing when rendering
	int advance;        // x advance when rendering
} info[NUM_GLYPHS];

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("usage: %s <font> <size>\n", argv[0]);
		return 1;
	}

	FT_Library ft;
	FT_Face    face;

	FT_Init_FreeType(&ft);
	FT_New_Face(ft, argv[1], 0, &face);
	FT_Set_Char_Size(face, 0, atoi(argv[2]) << 6, 96, 96);

	// quick and dirty max texture size estimate

	int max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(NUM_GLYPHS));
	int tex_width = 1;
	while (tex_width < max_dim) tex_width <<= 1;
	int tex_height = tex_width;

	// render glyphs to atlas

	char* pixels = (char*)calloc(tex_width * tex_height, 1);
	int pen_x = 0, pen_y = 0;

	for (int i = 0; i < NUM_GLYPHS; ++i) {
		FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
		FT_Bitmap* bmp = &face->glyph->bitmap;

		if (pen_x + bmp->width >= tex_width) {
			pen_x = 0;
			pen_y += ((face->size->metrics.height >> 6) + 1);
		}

		for (int row = 0; row < bmp->rows; ++row) {
			for (int col = 0; col < bmp->width; ++col) {
				int x = pen_x + col;
				int y = pen_y + row;
				pixels[y * tex_width + x] = bmp->buffer[row * bmp->pitch + col];
			}
		}

		// this is stuff you'd need when rendering individual glyphs out of the atlas

		info[i].x0 = pen_x;
		info[i].y0 = pen_y;
		info[i].x1 = pen_x + bmp->width;
		info[i].y1 = pen_y + bmp->rows;

		info[i].x_off = face->glyph->bitmap_left;
		info[i].y_off = face->glyph->bitmap_top;
		info[i].advance = face->glyph->advance.x >> 6;

		pen_x += bmp->width + 1;
	}

	FT_Done_FreeType(ft);

	// write png

	char* png_data = (char*)calloc(tex_width * tex_height * 4, 1);
	for (int i = 0; i < (tex_width * tex_height); ++i) {
		png_data[i * 4 + 0] |= pixels[i];
		png_data[i * 4 + 1] |= pixels[i];
		png_data[i * 4 + 2] |= pixels[i];
		png_data[i * 4 + 3] = 0xff;
	}

	stbi_write_png("font_output.png", tex_width, tex_height, 4, png_data, tex_width * 4);

	free(png_data);
	free(pixels);

	return 0;

#endif
#pragma endregion

#pragma region IMAGE_LOADING_TEST
#if 0
int main()
{
	const char* filename = "img/test_2_24BIT.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP* dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);


	bits = FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	unsigned short bitsPerPixel = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);

	std::cout << "w: " << width << ", h: " << height << ", bpp: " << bitsPerPixel << endl;

	for (int y = 0; y < height; y++)
	{
		BYTE* pixel = (BYTE*)bits;
		for (int x = 0; x < width; x++)
		{
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << endl;
			pixel += 3;
		}
		bits += pitch;
	}

	FreeImage_Unload(dib);

	return 0;
}
#endif
#pragma endregion

#pragma region SOUND_TEST
#include <irrKlang.h>
#if 0

int main()
{
#if 0
	using namespace golden;
	using namespace sound;

	SoundManager::add(new Sound("guitar", "music/guitar.wav"));
	SoundManager::add(new Sound("barbarian", "music/barbarian.wav"));

	SoundManager::play("barbarian");

	char i = 0;
	std::cin >> i;

	return 0
#endif

#if 0
		irrklang::ISoundEngine * sound_engine = irrklang::createIrrKlangDevice();

	if (!sound_engine)
	{
		std::cout << "irrklang error!" << endl;
		return 0;
	}

	sound_engine->play2D("guitar.wav", false);

	char i = 0;
	std::cin >> i;

	sound_engine->drop();
	return 0;
#endif
}

#endif
#pragma endregion