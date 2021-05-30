#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace golden { namespace graphics {

	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double mx, my;
	public:
		Window(const char* title, int width, int height);
		~Window();
		void clear() const;
		void update(); // swap buffers and poll events
		bool closed() const; // check if window should be closed

		inline int getWidth() const { return m_Width; };
		inline int getHeight() const { return m_Height; };

		bool isKeyPressed(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;
	private:
		bool init();
		friend static void window_resize(GLFWwindow* window, int width, int height);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void error_callback(int error, const char* description);
	};
}}