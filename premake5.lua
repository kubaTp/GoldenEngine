workspace "GoldenEngine"
	architecture "x84"

	system {"Windows", "Unix", "Mac"}

	configurations
	{
		"Debug",
		"Release"
	}

project "GoldenEngine-core"
	location "GoldenEngine-core"
	kind "ConsoleApp"
	language "C++"

	defines { 
	"_CRT_SECURE_NO_WARNINGS",
	"_CRT_SECURE_NO_DEPRECATE",
	"GLEW_STATIC",
	"FT2_BUILD_LIBRARY",
	"_LIB" }
	
	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"

	files { "GoldenEngine-core/src/**.cpp",
			"GoldenEngine-core/src/**.h" }

	includedirs {
		"Dependencies/Dependencies/GLFW/include/GLFW",
		"Dependencies/GLEW/include/GL",
		"Dependencies/FreeImage/include",
		"Dependencies/irrklang/include"
	}

	--add libraries path
	libdirs {
		"Dependencies/FreeImage/lib",
		"Dependencies/GLEW/lib",
		"Dependencies/GLFW/lib-vc2019",
		"Dependencies/irrklang/bin"
	}

	--libraries to be linked on Windows
	filter "system:Windows"
		system "windows"
		
		link { 
			""
		}