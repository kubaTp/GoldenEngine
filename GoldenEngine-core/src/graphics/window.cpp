#include "window.h"

namespace golden { namespace graphics {

	void window_resize(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void error_callback(int error, const char* description);

	Window::Window(const char* title, uint16_t width, uint16_t height) : m_Title(title), m_Width(width), m_Height(height)
	{
		if (!init())
			glfwTerminate();

		for (short i = 0; i < MAX_KEYS; i++) // default key setting
		{
			m_Keys[i] = false;
			m_KeysState[i] = false;

			if (i < MAX_BUTTONS)
			{
				m_MouseButtons[i] = false;
				m_MouseButtonState[i] = false;
			}
		}
	}

	Window::~Window() { glfwTerminate(); }

	bool Window::init()
	{
		glfwSetErrorCallback(error_callback); // set error callback before initializing

		if (!glfwInit()) // check initializing of GLFW
		{
			std::cout << "FAILED TO INITIALIZED GLFW!" << std::endl;
			return false;
		}

		m_Time = glfwGetTime();
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL); // create new window

		if (!m_Window) // if window has not been created
		{
			glfwTerminate();
			std::cout << "FAILED TO CREATE GLFW WINDOW!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window); // make context of current window called m_Window
		glfwSetWindowUserPointer(m_Window, this); // set pointer to current window to set all callback properly
		glfwSetFramebufferSizeCallback(m_Window, window_resize); // set resize callback
		glfwSetKeyCallback(m_Window, key_callback); // set key callback
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback); // set mouse button callback
		glfwSetCursorPosCallback(m_Window, cursor_position_callback); // set cursor callback
		glfwSwapInterval(0); // turn off v-sync

		if (glewInit() != GLEW_OK) // check GLEW
		{
			std::cout << "GLEW COULD NOT BE INITIALIZED!" << std::endl;
			return false;
		}

		// make context for imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsClassic();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		Logger::logGoldenEngine();

		glEnable(GL_BLEND); // enable blending for alfa
		//glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glDepthFunc(GL_LESS);
		return true;
	}

	void Window::clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	bool Window::isKeyPressed(uint16_t keycode) const
	{
		if (keycode >= MAX_KEYS)
		{
			return false;
		}

		return m_Keys[keycode];
	}

	bool Window::isKeyPressedDown(uint16_t keycode) const
	{
		if (keycode >= MAX_KEYS)
			return false;

		if (m_Keys[keycode])
		{
			if (!m_KeysState[keycode])
				return true;
			else
				return false;
		}

		return false;
	}

	bool Window::isMouseButtonPressed(uint16_t button) const
	{
		//TODO: log this
		if (button >= MAX_BUTTONS)
		{
			return false;
		}

		return m_MouseButtons[button];
	}

	bool Window::isMouseButtonPressedDown(uint16_t button) const
	{
		if (button >= MAX_BUTTONS)
			return false;

		if (m_MouseButtons[button])
		{
			if (!m_MouseButtonState[button])
				return true;
		}

		return false;
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = m_Mx;
		y = m_My;
	}

	float Window::getKeyboardInput(Input input)
	{
		static float resultHorizontal = 0;
		static float resultVertical = 0;

		if (input == Input::Horizontal)
		{
			if (isKeyPressed(GLFW_KEY_A))
			{
				resultHorizontal -= 4 * m_Timestep.getSeconds();
				//std::cout << resultHorizontal << std::endl;
			}
			else if (isKeyPressed(GLFW_KEY_D))
			{
				resultHorizontal += 4 * m_Timestep.getSeconds();
				//std::cout << resultHorizontal << std::endl;
			}

			return resultHorizontal;
		}
		else
		{
			if (isKeyPressed(GLFW_KEY_W))
			{
				resultVertical += 5 * m_Timestep.getSeconds();
			}
			else if (isKeyPressed(GLFW_KEY_S))
			{
				resultVertical -= 5 * m_Timestep.getSeconds();
			}

			return resultVertical;
		}
	}

	void Window::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Golden Engine OpenGL error: " << error << std::endl;

		memcpy(m_KeysState, m_Keys, MAX_KEYS * sizeof(bool)); // copy current state of keys to array which stores last frame state of keys
		memcpy(m_MouseButtonState, m_MouseButtons, MAX_BUTTONS * sizeof(bool));

		m_Time = (float)glfwGetTime(); // update current time
		m_Timestep = m_Time - m_LastFrameTime;
		m_LastFrameTime = m_Time;

		static uint32_t deltaTime = 0;
		static uint16_t frameCounter = 0;
		frameCounter++;

		if (m_Time - deltaTime >= 1) // check if delta time is greater than 1
		{
			fps = frameCounter; // set public fps variable value to frameCounter var value
			frameCounter = 0;
			deltaTime++;
		}

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::closed() const { return glfwWindowShouldClose(m_Window) == 1; }

	// CALLBACKS
	void window_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Mx = xpos;
		win->m_My = ypos;
	}

	void error_callback(int error, const char* description)
	{
		std::cout << "Error: " << description << std::endl;
	}
}}