workspace "GoldenEngine"
	architecture "x84"

	configurations
	{
		"Debug",
		"Release"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }

   filter "configurations:Release"
		defines { "NDEBUG" }

project "GoldenEngine-core"
	location "GoldenEngine-core"
	kind "ConsoleApp"
	language "C++"

	defines { "_CRT_SECURE_NO_WARNINGS;_CRT_SECURE_NO_DEPRECATE;GLEW_STATIC;_CONSOLE;FT2_BUILD_LIBRARY;_LIB;" }
	files { "src/**.cpp",
			"src/**.h" }
