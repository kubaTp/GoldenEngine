-- after building copy dll's from dependencies to target directory may use command for this
workspace "GoldenEngine"
	architecture "x32"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GoldenEngine-core"
	location "GoldenEngine-core"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir)
	objdir("bin/int/" .. outputdir)

	--ok, err = os.copyfile("${wks.location}/Dependecies/irrklang/lib/dll/irrKlang.dll", "${cfg.targetdir}")
	--prelinkcommands { "{COPY} ../Dependencies/irrklang/lib/irrKlang.dll %{cfg.targetdir}" }

	files { "%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.h",
			"%{prj.name}/app.cpp",
			"%{prj.name}/core.h",

			--fretype and freetype-gl files
			"%{prj.name}/extLibs/freetype-gl/**.h",
			"%{prj.name}/extLibs/freetype-gl/**.c",
			"%{prj.name}/extLibs/freetype/include/ft2build.h",
			"%{prj.name}/extLibs/freetype/include/freetype/config/*.h",
			"%{prj.name}/extLibs/freetype/src/autofit/autofit.c",
			"%{prj.name}/extLibs/freetype/src/base/ftbase.c", 
			"%{prj.name}/extLibs/freetype/src/base/ftbbox.c",
			"%{prj.name}/extLibs/freetype/src/base/ftbdf.c",
			"%{prj.name}/extLibs/freetype/src/base/ftbitmap.c",
			"%{prj.name}/extLibs/freetype/src/base/ftcid.c",
			"%{prj.name}/extLibs/freetype/src/base/ftdebug.c",
			"%{prj.name}/extLibs/freetype/src/base/ftfstype.c",
			"%{prj.name}/extLibs/freetype/src/base/ftgasp.c",
			"%{prj.name}/extLibs/freetype/src/base/ftglyph.c",
			"%{prj.name}/extLibs/freetype/src/base/ftgxval.c",
			"%{prj.name}/extLibs/freetype/src/base/ftinit.c",
			"%{prj.name}/extLibs/freetype/src/base/ftmm.c",
			"%{prj.name}/extLibs/freetype/src/base/ftotval.c",
			"%{prj.name}/extLibs/freetype/src/base/ftpatent.c",
			"%{prj.name}/extLibs/freetype/src/base/ftpfr.c",
			"%{prj.name}/extLibs/freetype/src/base/ftstroke.c",
			"%{prj.name}/extLibs/freetype/src/base/ftsynth.c",
			"%{prj.name}/extLibs/freetype/src/base/ftsystem.c",
			"%{prj.name}/extLibs/freetype/src/base/fttype1.c",
			"%{prj.name}/extLibs/freetype/src/base/ftwinfnt.c",
			--bdf
			"%{prj.name}/extLibs/freetype/src/bdf/bdf.c",
			--cache
			"%{prj.name}/extLibs/freetype/src/cache/ftcache.c",
			--cff
			"%{prj.name}/extLibs/freetype/src/cff/cff.c",
			--cid
			"%{prj.name}/extLibs/freetype/src/cid/type1cid.c",
			--gzip
			"%{prj.name}/extLibs/freetype/src/gzip/ftgzip.c",
			--lzw
			"%{prj.name}/extLibs/freetype/src/lzw/ftlzw.c",
			--pcf
			"%{prj.name}/extLibs/freetype/src/pcf/pcf.c",
			"%{prj.name}/extLibs/freetype/src/pfr/pfr.c",
			"%{prj.name}/extLibs/freetype/src/psaux/psaux.c",
			"%{prj.name}/extLibs/freetype/src/pshinter/pshinter.c",
			"%{prj.name}/extLibs/freetype/src/psnames/psmodule.c",
			"%{prj.name}/extLibs/freetype/src/raster/raster.c",
			"%{prj.name}/extLibs/freetype/src/sfnt/sfnt.c",
			"%{prj.name}/extLibs/freetype/src/smooth/smooth.c",
			"%{prj.name}/extLibs/freetype/src/truetype/truetype.c",
			"%{prj.name}/extLibs/freetype/src/type1/type1.c",
			"%{prj.name}/extLibs/freetype/src/type42/type42.c",
			"%{prj.name}/extLibs/freetype/src/winfonts/winfnt.c",

			--imgui
			"%{prj.name}/extLibs/imgui/**.h",
			"%{prj.name}/extLibs/imgui/**.cpp",

			--stb_image
			"%{prj.name}/extLibs/stb-image/*.h",
			"%{prj.name}/extLibs/stb-image/*.cpp",

			--golden engine files
			"%{prj.name}/src/base.h",
			"%{prj.name}/src/core.h",
			"%{prj.name}/src/gebase.h"
		 }

	includedirs {
		"%{wks.location}/Dependencies/GLEW/include",
		"%{wks.location}/Dependencies/GLFW/include",
		"%{wks.location}/Dependencies/irrklang/include",
		"%{wks.location}/%{prj.name}/extLibs/freetype/include",
		"%{wks.location}/%{prj.name}/extLibs/freetype/include/**"
	}

	--add libraries path
	libdirs {
		"%{wks.location}/Dependencies/GLEW/lib",
		"%{wks.location}/Dependencies/GLFW/lib-vc2019",
		"%{wks.location}/Dependencies/irrklang/bin"
	}

	cppdialect "C++17"

	--libraries to be linked
	links { 
		"irrKlang.lib",
		"glfw3.lib",
		"opengl32.lib",
		"glew32s.lib"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"_CRT_SECURE_NO_DEPRECATE",
		"GLEW_STATIC",
		"_CONSOLE",
		"FT2_BUILD_LIBRARY"
	}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"
		