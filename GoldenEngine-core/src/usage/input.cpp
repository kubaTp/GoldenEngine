#include "input.h"

namespace golden {  namespace usage {

	bool Input::m_Keys[MAX_KEYS];
	bool Input::m_KeysState[MAX_KEYS];
	bool Input::m_MouseButtons[MAX_BUTTONS];
	bool Input::m_MouseButtonState[MAX_BUTTONS];
	double Input::m_Mx, Input::m_My;

	void Input::init()
	{
		for (short i = 0; i < MAX_KEYS; i++) // default key setting
		{
			m_Keys[i] = false;
			//m_KeysState[i] = false;

			if (i < MAX_BUTTONS)
			{
				m_MouseButtons[i] = false;
				//m_MouseButtonState[i] = false;
			}
		}
	}
	void Input::update()
	{
		memcpy(m_KeysState, m_Keys, MAX_KEYS * sizeof(bool)); // copy current state of keys to array which stores last frame state of keys
		memcpy(m_MouseButtonState, m_MouseButtons, MAX_BUTTONS * sizeof(bool));
	}

	bool Input::isKeyPressed(uint16_t keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}
	bool Input::isKeyPressedDown(uint16_t keycode)
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
	bool Input::isMouseButtonPressed(uint16_t button)
	{
		if (button >= MAX_BUTTONS)
		{
			return false;
		}

		return m_MouseButtons[button];
	}
	bool Input::isMouseButtonPressedDown(uint16_t button)
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
	void Input::getMousePosition(double& x, double& y)
	{
		x = m_Mx;
		y = m_My;
	}

	float Input::getKeyboardInput(InputKind input)
	{
		static float resultHorizontal = 0;
		static float resultVertical = 0;

		switch (input)
		{
			case InputKind::Horizontal:
				if (isKeyPressed(GLFW_KEY_A))
					resultHorizontal -= 4 * Time::m_Timestep.getSeconds();

				else if (isKeyPressed(GLFW_KEY_D))
					resultHorizontal += 4 * Time::m_Timestep.getSeconds();

				return resultHorizontal;

				break;

			case InputKind::Vertical:
				if (isKeyPressed(GLFW_KEY_W))
					resultVertical += 5 * Time::m_Timestep.getSeconds();

				else if (isKeyPressed(GLFW_KEY_S))
					resultVertical -= 5 * Time::m_Timestep.getSeconds();

				return resultVertical;

				break;
		}
	}
}}