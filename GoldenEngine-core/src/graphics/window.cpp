#include "window.h"

namespace golden { namespace graphics {

	void window_resize(GLFWwindow* window, int width, int height);
	void error_callback(int error, const char* description);

	Window::Window(const char* title, uint16_t width, uint16_t height, bool initIn3dMode) : m_Title(title), m_Width(width), m_Height(height)
	{
		if (!initIn3dMode)
			init();
		else
			init3d_func();

		usage::Time::init();
		usage::Input::init();
	}

	Window::~Window() { glfwTerminate(); }

	void Window::init()
	{
		glfwSetErrorCallback(error_callback); // set error callback before initializing

		GE_ASSERT(!glfwInit(), "failed to initialized glfw"); // failed to init glfw

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL); // create new window

		GE_ASSERT(!m_Window, "failed to create window"); // failed to create glfw window
			

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwMakeContextCurrent(m_Window); // make context of current window called m_Window
		glfwSetWindowUserPointer(m_Window, this); // set pointer to current window to set all callback properly
		glfwSetFramebufferSizeCallback(m_Window, window_resize); // set resize callback
		glfwSetKeyCallback(m_Window, usage::key_callback); // set key callback
		glfwSetMouseButtonCallback(m_Window, usage::mouse_button_callback); // set mouse button callback
		glfwSetCursorPosCallback(m_Window, usage::cursor_position_callback); // set cursor callback
		glfwSwapInterval(0); // turn off v-sync

		GE_ASSERT(glewInit() != GLEW_OK, "glew could not be intiliazed"); // check glew

		IMGUI_CHECKVERSION(); // make context for imgui
		//glClipControl(GL_UPPER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); 
		(void)io;
		io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsClassic();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		Logger::logGoldenEngine();

		glEnable(GL_BLEND); // enable blending for alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Icon.pixels = ImageLoader::loadImageNeutralWithoutChannel(ResourceLoader::findFile("img/transparent.png"), &m_Icon.width, &m_Icon.height); // change this to project path
		GE_ASSERT(m_Icon.pixels == nullptr, "Golden Engine error : failed to load image at path " + ResourceLoader::findFile("img/transparent.png"));
		glfwSetWindowIcon(m_Window, 1, &m_Icon);
		ImageLoader::deleteData(m_Icon.pixels);
	}

	void Window::init3d_func()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(820, 600, "3D Sanbox", NULL, NULL);

		if (m_Window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_Window);

		GE_ASSERT(glewInit() != GLEW_OK, "glew could not be intiliazed"); // check glew

		glViewport(0, 0, 820, 600);

		glEnable(GL_DEPTH_TEST);
		glfwSwapInterval(1);
	}

	void Window::clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void Window::update()
	{
		GLenum error = glGetError();
		GE_ASSERT_OPENGL_WARNING(error != GL_NO_ERROR, "OpenGL Error : ", error);

		usage::Time::update(); // set current time in 'Time' static class
		usage::Input::update(); // update states of keys and buttons

		static uint32_t deltaTime = 0;
		static uint16_t frameCounter = 0;
		frameCounter++;

		if (usage::Time::getTime() - deltaTime >= 1) // check if delta time is greater than 1
		{
			fps = frameCounter; // set public fps variable value to frameCounter var value
			frameCounter = 0;
			deltaTime++;
		}

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	//bool Window::closed() const { return glfwWindowShouldClose(m_Window) == 1; }

	void Window::setWindowIcon(const std::string& imagePath)
	{
		m_Icon.pixels = ImageLoader::loadImageNeutralWithoutChannel(imagePath, &m_Icon.width, &m_Icon.height); // change this to project path
		GE_ASSERT(m_Icon.pixels == nullptr, "failed to load image at path " + imagePath);
		glfwSetWindowIcon(m_Window, 1, &m_Icon);
		ImageLoader::deleteData(m_Icon.pixels);
	}

	// CALLBACK AND ERRORS
	void window_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height); // TODO : check this in the future
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;

		// call Golden Engine resize callback
		win->ChiefResizeCallbackFunc();
	}

	void error_callback(int error, const char* description)
	{
		Logger::logWarning(description);
	}
}}