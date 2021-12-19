#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/timer.h"
#include "../utils/assert.h"
#include "../utils/logger.h"
#include "../utils/timestep.h"
#include "../utils/imageloader.h"
#include "../utils/resourceloader.h"
#include "../usage/input.h"

#include "../../extLibs/imgui/imgui.h"
#include "../../extLibs/imgui/impl/imgui_impl_glfw.h"
#include "../../extLibs/imgui/impl/imgui_impl_opengl3.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace golden { namespace graphics {

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
		inline GLFWimage getWindowIcon() const { return m_Icon; }

		inline float getTime() const { return m_Time; }
		inline float getTimestep() const { return m_Timestep.getSeconds(); }
		inline float getTimestepMiliSecs() const { return m_Timestep.getMiliseconds(); }
		
		inline void setWindowIcon(const std::string& imagePath);

		friend class usage::Input;
	private:
		bool init();

		friend static void window_resize(GLFWwindow* window, int width, int height);
		friend static void error_callback(int error, const char* description);

	private:
		const char* m_Title;
		uint16_t m_Width, m_Height;
		GLFWwindow* m_Window;
		GLFWimage m_Icon;

		float m_Time;
		float m_LastFrameTime = 0.0f;
		Timestep m_Timestep = 0.0f;
	};
}}