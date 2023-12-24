project "Color"
	language "C++"
	cppdialect "C++20"
	kind "StaticLib"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir    "%{OutputDir.Intermediates}/%{prj.name}"
	
	pchheader "ColorPCH.h"
	pchsource "Source/ColorPCH.cpp"
	
	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"Source",
		"Source/Color"
	}
	
	defines
	{
		-- MSVC-related warning-error disabling
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"CL_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		defines
		{
			"CL_PLATFORM_LINUX"
		}
	
	filter "configurations:Development"
		runtime "Debug"
		symbols "On"
		defines
		{
			"CL_DEVELOPMENT"
		}
	
	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_PREVIEW"
		}
	
	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_SHIPPING"
		}
	