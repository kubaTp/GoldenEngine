workspace "GoldenEngine"
	architecture "x84"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

project "GoldenEngine-core"
	location "GoldenEngine-core"
	kind "ConsoleApp"
	language "C++"

	targetdir
	_CRT_SECURE_NO_WARNINGS;_CRT_SECURE_NO_DEPRECATE;GLEW_STATIC;_CONSOLE;FT2_BUILD_LIBRARY;_LIB;
