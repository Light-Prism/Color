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
		"Source/Color",

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.VulkanSDK}",
	}
	
	defines
	{
		-- MSVC-related warning-error disabling
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"stb"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"CL_PLATFORM_WINDOWS"
		}
		
		removefiles
		{
			"Source/Platform/Linux/**.cpp"
		}
	
	filter "system:linux"
		defines
		{
			"CL_PLATFORM_LINUX"
		}
		
		removefiles
		{
			"Source/Platform/Windows/**.cpp"
		}
	
	filter "configurations:Development"
		runtime "Debug"
		symbols "On"

		defines
		{
			"CL_DEVELOPMENT"
		}

		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Preview or Shipping"
		runtime "Release"
		optimize "Speed"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
	
	filter "configurations:Preview"
		defines
		{
			"CL_PREVIEW"
		}
	
	filter "configurations:Shipping"
		defines
		{
			"CL_SHIPPING"
		}
	