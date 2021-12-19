#define PREDEFINED_MACROS
#include "src/core.h"

#define BATCH_RENDERER 1
#define MAX_SPRITE_AMOUNT 0

#define CHIEF_RENDERING 1

#define GE_EDITOR 0
// projection matrix is maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 1.0f, -1.0f)
// TODO : scene abstraction ( framebuffer in chief )
// TODO : implement ECS

void CustomStartMethod()
{
	golden::Logger::logInfo("Custom start method behaviour");
	//exit(0);
}

void CustomUpdateMethod()
{
	golden::Logger::logInfo("Custom update method behaviour");
}

#if 1
int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;
	using namespace sound;

	system("CLS");
	srand(time(NULL));

	rs::setResourcePath("D:/Code/Games Engine/practice/GoldenEngine/assets/");

	SoundManager::add(new Sound("guitar", rs::findFile("music/guitar.wav"), true));
	SoundManager::add(new Sound("barbarian", rs::findFile("music/barbarian.wav"), true));
	SoundManager::add(new Sound("buttonclick", rs::findFile("music/buttonclick.mp3")));
	SoundManager::add(new Sound("menu", rs::findFile("music/menumusic.mp3")));

	Window window("Golden Engine", 960.0f, 540.0f);
	window.clear();

	Chief::init(new BatchRenderer2D());

	Shader shader_lighting(rs::findFile("shaders/basic.vert"), rs::findFile("shaders/basic.frag"));
	Shader shader(rs::findFile("shaders/basic.vert"), rs::findFile("shaders/font.frag"));
	Shader font_shader(rs::findFile("shaders/basic.vert"), rs::findFile("shaders/font.frag"));

	shader_lighting.enable();
	shader_lighting.setUniform2f("light_pos", Vec2(0, 0));

	TileLayer layer(shader);
	TileLayer background_layer(shader_lighting);
	TileLayer uiLayer(font_shader);

	Chief::addLayer("layer", &layer);
	Chief::addLayer("uiLayer", &uiLayer);
	Chief::addLayer("bg_layer", &background_layer);

	Chief::descLayers();

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

	Sprite* sky_bg = new Sprite(-16.0f, -9.0f, 32, 20, &textures[3]);
	background_layer.add(sky_bg);

	Sprite* transparentSprite = new Sprite(-3, -3, 3, 3, &textures[2]);
	layer.add(transparentSprite); // transparent one sprite

	#if 0
		layer.add(new Sprite(2.5f, -2, 4, 4, &textures[0])); // 24 bit one sprite
		layer.add(new Sprite(7.0f, -2, 4, 4, Vec4(1, 1, 1, 1)));
	#endif

	FontManager::add(new Font(FontType::Inter_Regular, rs::findFile("fonts/Inter-Regular.ttf"), 21));
	FontManager::add(new Font(FontType::Jura, rs::findFile("fonts/Jura.ttf"), 29));
	FontManager::add(new Font(FontType::SourceSerifPro, rs::findFile("fonts/SourceSerifPro-Regular.ttf"), 21));

	Label* fpsLabel = new Label("fps: 0", -15.5f, 8.0f, FontType::Inter_Regular, 0xffffffff);
	Label* nameLabel = new Label("Project: Sandbox", 8.0f, 8.0f, FontType::Inter_Regular, 0xffffffff);
	uiLayer.add(fpsLabel);
	uiLayer.add(nameLabel);

	// TODO : add it in shader class
	GLint textIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", textIDs, 10);
	shader.disabled();

	shader_lighting.enable();
	shader_lighting.setUniform1iv("textures", textIDs, 10);
	shader_lighting.disabled();

	double x, y;
	
	Mat4 rotationMatrix = Mat4::idenity();
	//Mat4 translationMatrix = Mat4::idenity();

	SoundManager::changeVolume(0.3f);
	float deltaTime = 0.0f, volume = SoundManager::getVolume();
	Vec3 newPos;

	//transparentSprite->setStart(&CustomStartMethod);
	transparentSprite->getComponent("BehaviourComponent")->setOnStartFunction(&CustomStartMethod);
	transparentSprite->getComponent("BehaviourComponent")->setOnUpdateFunction(&CustomUpdateMethod);

	//transparentSprite->setUpdate(&CustomUpdateMethod);

	/*--- GAME LOOP ---*/
	while (!window.closed())
	{
		static bool firstFrame = true;
		deltaTime += 0.001f;
		window.clear();

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

		if (firstFrame) // start method
		{	
			SoundManager::changeVolume(0.6f);
			SoundManager::play("menu");
			//SoundManager::muteAudio();
			firstFrame = false;
		}


		//rotationMatrix = Mat4::rotation(40, Vec3(0, 0, 1));
		//rotationMatrix = Mat4::translation(Vec3(4.0f, 0.0f, 0.0f));
		
		//shader.enable();
		//shader.setUniformMat4("ml_matrix", rotationMatrix);
		//shader.disabled();


		//SoundManager::changeVolume(volume);

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
		//shader_lighting.enable();
		//shader_lighting.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		//shader_lighting.disabled();

		newPos = Vec3(usage::Input::getKeyboardInput(usage::InputKind::Horizontal), usage::Input::getKeyboardInput(usage::InputKind::Vertical), 0);
		transparentSprite->setPosition(&newPos);

		//rotationMatrix = Mat4::rotation(window.getTime() * 10, Vec3(0, 0, 1));
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

		Chief::render();
		//Chief::render("layer");

#if GE_EDITOR
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		window.update();

	}

	SoundManager::destroy();
	return 0;
}
#endif

#pragma region EXT_TEST
#if 0
int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;
	using namespace sound;

	system("CLS");
	srand(time(NULL));

	rs::setResourcePath("D:/Code/Games Engine/GoldenEngine/assets/");

	Window window("fb test", 960, 512);
	window.clear();

	Simple2DRenderer renderer;

	Shader shader(rs::findFile("shaders/simple.vert"), rs::findFile("shaders/simple.frag"));
	StaticSprite sprite(-2, -2, 4, 4, Vec4(0.2f , 0.3f, 0.4f, 1), shader);

	renderer.submit(&sprite);

	/*--- GAME LOOP ---*/
	while (!window.closed())
	{

		// render
		renderer.submit(&sprite);
		renderer.flush();

		window.update();
	}

	SoundManager::destroy();
	return 0;
}
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

#pragma region 3D_TEST
#if 0

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main(void)
{
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glViewport(0.0f, 0.0f, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
	GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glTranslatef(halfScreenWidth, halfScreenHeight, -500);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

		DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);

		glPopMatrix();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}



void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << key << std::endl;

	const GLfloat rotationSpeed = 10;

	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			rotationX -= rotationSpeed;
			break;
		case GLFW_KEY_S:
			rotationX += rotationSpeed;
			break;
		case GLFW_KEY_D:
			rotationY += rotationSpeed;
			break;
		case GLFW_KEY_A:
			rotationY -= rotationSpeed;
			break;
		}
	}
}

void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
	GLfloat halfSideLength = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		// front face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// back face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

		// left face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// right face
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// top face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

		// top face
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glColor3f( colour[0], colour[1], colour[2] );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
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
