#include "window.h"

namespace golden { namespace graphics {

	void window_resize(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void error_callback(int error, const char* description);

	Window::Window(const char* title, int width, int height) : m_Title(title), m_Width(width), m_Height(height)
	{
		init();

		for (short i = 0; i < MAX_KEYS; i++)
			m_Keys[i] = false;

		for (short i = 0; i < MAX_BUTTONS; i++)
			m_MouseButtons[i] = false;
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

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL); // create new window

		if (!m_Window) // if window has not been created
		{
			glfwTerminate();
			std::cout << "FAILED TO CREATE GLFW WINDOW!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window); // make context of current window called m_Window
		glfwSetWindowUserPointer(m_Window, this); // set pointer to current window to set all callback properly
		glfwSetWindowSizeCallback(m_Window, window_resize); // set resize callback
		glfwSetKeyCallback(m_Window, key_callback); // set key callback
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback); // set mouse button callback
		glfwSetCursorPosCallback(m_Window, cursor_position_callback); // set cursor callback

		glfwSwapInterval(0); // turn off v-sync

		;			if (glewInit() != GLEW_OK) // check GLEW
		{
			std::cout << "GLEW COULD NOT BE INITIALIZED!" << std::endl;
			return false;
		}
		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	void Window::clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
		{
			return false;
		}

		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		//TODO: log this!!!!
		if (button >= MAX_BUTTONS)
		{
			return false;
		}

		return m_MouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = mx;
		y = my;
	}

	void Window::update()
	{
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
		win->mx = xpos;
		win->my = ypos;
	}

	void error_callback(int error, const char* description)
	{
		std::cout << "Error: " << description << std::endl;
	}
}}