#pragma once

#include <GLFW/glfw3.h>
#include "../utils/timestep.h"

#include <iostream>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace golden {

	namespace graphics {

		class Window;
	}

	namespace usage {

		enum struct InputKind { Horizontal, Vertical };

		class Input
		{
		private:
			Input() { }
			friend class graphics::Window;

		public:
			static bool isKeyPressed(uint16_t keycode);
			static bool isKeyPressedDown(uint16_t keycode);
			static bool isMouseButtonPressed(uint16_t button);
			static bool isMouseButtonPressedDown(uint16_t button);
			static void getMousePosition(double& x, double& y);

			static float getKeyboardInput(InputKind input);
			static void getKeyboardInput(InputKind input, float& value) { value = getKeyboardInput(input); }

		private:
			// Callbacks for window
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Input::m_Keys[key] = action != GLFW_RELEASE;
			}
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
			{
				Input::m_MouseButtons[button] = action != GLFW_RELEASE;
			}
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
			{
				Input::m_Mx = xpos;
				Input::m_My = ypos;
			}

			static void init(Timestep& timestep);
			static void update();

		private:
			static bool m_Keys[MAX_KEYS]; // true if key is pressed
			static bool m_KeysState[MAX_KEYS]; // holds the state of key in previous frame to setup isKeyDown()
			static bool m_MouseButtons[MAX_BUTTONS];
			static bool m_MouseButtonState[MAX_BUTTONS];
			static double m_Mx, m_My;

			static Timestep* m_Timestep;
		};
	}
}