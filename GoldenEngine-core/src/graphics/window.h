#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/timer.h"
#include "../utils/logger.h"
#include "../utils/timestep.h"

#include "../../extLibs/imgui/imgui.h"
#include "../../extLibs/imgui/impl/imgui_impl_glfw.h"
#include "../../extLibs/imgui/impl/imgui_impl_opengl3.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace golden {
	namespace graphics {

		enum struct Input { Horizontal, Vertical };

		class Window
		{
		public:
			uint16_t fps = 0;
		public:
			Window(const char* title, uint16_t width, uint16_t height);
			~Window();

			void clear() const;
			void update(); // swap buffers and poll events
			bool closed() const; // check if window should be closed

			inline uint16_t getWidth() const { return m_Width; };
			inline uint16_t getHeight() const { return m_Height; };
			inline GLFWwindow* getWindow() const { return m_Window; }
			inline float getTime() const { return m_Time; }
			inline float getTimestep() const { return m_Timestep.getSeconds();}
			inline float getTimestepMiliSecs() const { return m_Timestep.getMiliseconds(); }

			bool isKeyPressed(uint16_t keycode) const;
			bool isKeyPressedDown(uint16_t keycode) const;
			bool isMouseButtonPressed(uint16_t button) const;
			bool isMouseButtonPressedDown(uint16_t button) const;
			void getMousePosition(double& x, double& y) const;
			float getKeyboardInput(Input input);
			void getKeyboardInput(Input input, float& value) { value = getKeyboardInput(input); }

		private:
			bool init();
			friend static void window_resize(GLFWwindow* window, int width, int height);
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			friend static void error_callback(int error, const char* description);

		private:
			const char* m_Title;
			uint16_t m_Width, m_Height;
			GLFWwindow* m_Window;

			bool m_Keys[MAX_KEYS]; // true if key is pressed
			bool m_KeysState[MAX_KEYS]; // holds the state of key in previous frame to setup isKeyDown()
			bool m_MouseButtons[MAX_BUTTONS];
			bool m_MouseButtonState[MAX_BUTTONS];
			double m_Mx, m_My;

			float m_Time;
			float m_LastFrameTime = 0.0f;
			Timestep m_Timestep = 0.0f;
		};
	}
}