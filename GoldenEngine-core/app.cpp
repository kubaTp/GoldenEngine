#include "GoldenEngine_Core.h"

#include "time.h"

#ifdef AUDIO_TEST
	#include <irrKlang.h>
#endif

#define endl '\n'

#define BATCH_RENDERER 1
#define MAX_SPRITE_AMOUNT 0

// TODO: set up IMGUI

#if 1
int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;
	using namespace sound;

	system("CLS");
	srand(time(NULL));

	SoundManager::add(new Sound("guitar", "music/guitar.wav", true));
	SoundManager::add(new Sound("barbarian", "music/barbarian.wav", true));
	SoundManager::add(new Sound("buttonclick", "music/buttonclick.mp3"));
	SoundManager::add(new Sound("menu", "music/menumusic.mp3"));

	Window window("Golden Engine", 960.0f, 540.0f);
	window.clear();

	// projection matrix is maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 1.0f, -1.0f)

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader shader2("src/shaders/basic.vert", "src/shaders/font.frag");
	shader.enable();
	shader.setUniform2f("light_pos", Vec2(0, 0));

	TileLayer layer(shader);
	TileLayer background_layer(shader);
	TileLayer uiLayer(shader2);

	Texture textures[] =
	{
		Texture("img/24Bit_img_2.png"),
		Texture("img/24Bit_img_chess.png"),
		//Texture("img/24Bit_img_chess_2.png"),
		Texture("img/transparent.png"),
		Texture("img/sky.png")
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

	Sprite* transparentSprite = new Sprite(-2, -2, 4, 4, &textures[2]);
	layer.add(transparentSprite); // transparent one sprite

	#if 0
		layer.add(new Sprite(2.5f, -2, 4, 4, &textures[0])); // 24 bit one sprite
		layer.add(new Sprite(7.0f, -2, 4, 4, Vec4(1, 1, 1, 1)));
	#endif

	FontManager::add(new Font(FontType::Inter_Regular, "fonts/Inter-Regular.ttf", 21));
	FontManager::add(new Font(FontType::Jura, "fonts/Jura.ttf", 29));
	FontManager::add(new Font(FontType::SourceSerifPro, "fonts/SourceSerifPro-Regular.ttf", 21));

	Label* fpsLabel = new Label("fps: 0", -15.5f, 8.0f, FontType::Inter_Regular, 0xffffffff);
	Label* nameLabel = new Label("Golden Engine 1.0.01", 8.0f, 8.0f, FontType::Inter_Regular, 0xffffffff);
	uiLayer.add(fpsLabel);
	uiLayer.add(nameLabel);

	GLint textIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", textIDs, 10);

	double x, y;

	Mat4 rotationMatrix = Mat4::idenity();
	//Mat4 translationMatrix = Mat4::idenity();

	float deltaTime = 0.0f, f = 0.0f;
	bool showDemoWindow = false, showAnotherWindow = false;
	uint16_t counter = 0;
	Vec3 newPos;

	// GAME LOOP
	while (!window.closed())
	{
		static bool firstFrame = true;
		deltaTime += 0.001f;
		window.clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (showDemoWindow)
			ImGui::ShowDemoWindow();

		ImGui::Begin("Hello, world!");
		ImGui::Text("Test txt");
		ImGui::Checkbox("Show demo window", &showDemoWindow);
		ImGui::Checkbox("Another window", &showAnotherWindow);
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::SameLine();
		ImGui::Text("f: %f", f);
		if (ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter: %d", counter);
		ImGui::End();

		if (firstFrame) // start method
		{
			SoundManager::changeVolume(0.3f);
			//SoundManager::play("menu");
			firstFrame = false;
		}

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

		#pragma region BACKGROUND_MOVEMENT
#if 0
		
#endif
#pragma endregion

		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		newPos = Vec3(window.getKeyboardInput(Input::Horizontal), window.getKeyboardInput(Input::Vertical), 0) * transparentSprite->getPosition();
		transparentSprite->setPosition(&newPos);

		//rotationMatrix = Mat4::rotation(window.getTime() * 10, Vec3(0, 0, 1)); 

		shader.setUniformMat4("ml_matrix", rotationMatrix);

		background_layer.render();
		layer.render();
		uiLayer.render();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		fpsLabel->content = ("fps: " + std::to_string(window.fps));
		
		#pragma region INPUT_TESTING
#if 1
		if (window.isMouseButtonPressedDown(GLFW_MOUSE_BUTTON_1))
			std::cout << "mouse button 1 is down" << endl;

		//if (window.isMouseButtonDown(GLFW_MOUSE_BUTTON_1))
			//std::cout << "mouse button works 2 times per frame" << endl;

		if (window.isKeyPressedDown(GLFW_KEY_W) || window.isKeyPressedDown(GLFW_KEY_S) || window.isKeyPressedDown(GLFW_KEY_A) || window.isKeyPressedDown(GLFW_KEY_D))
			SoundManager::play("buttonclick");

		//if (window.isKeyDown(GLFW_KEY_T))
			//std::cout << "key works 2 times per frame" << endl;
#endif
	#pragma endregion

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
	system("CLS");

	using namespace golden;
	using namespace graphics;
	using namespace maths;
	using namespace sound;

	srand(time(NULL));

#if 0
	SoundManager::add(new Sound("guitar", "music/guitar.wav", true));
	SoundManager::add(new Sound("barbarian", "music/barbarian.wav", true));
	SoundManager::add(new Sound("buttonclick", "music/buttonclick.mp3"));
#endif

	SoundManager::add(new Sound("menu", "music/menumusic.mp3"));

	Window window("Golden Engine", 960.0f, 540.0f);
	window.clear();

	// GAME LOOP
	while (!window.closed())
	{
		static bool firstFrame = true;
		window.clear();

		if (firstFrame) // start method
		{
			SoundManager::changeVolume(0.3f);
			SoundManager::play("menu");
			firstFrame = false;
		}

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(0, 0.5f);
		glVertex2f(0.5f, 0.0f);
		glEnd();
		window.clear();

		window.update();
	}
	return 0;
}
#endif
#pragma endregion

#pragma region SOUND_TEST
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

#pragma region 3D_TESTING
#if 0

int main()
{
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
