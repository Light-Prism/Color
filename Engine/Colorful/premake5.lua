project "Colorful"
	language "C++"
	cppdialect "C++20"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir    "%{OutputDir.Intermediates}/%{prj.name}"
	
	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"Source",
		"%{SourceDir.Color}",
		"%{SourceDir.Color}/Color",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}
	
	defines
	{
		-- MSVC-related warning-error disabling
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	links
	{
		"Color"
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
		kind "ConsoleApp"
		runtime "Debug"
		symbols "On"
		defines
		{
			"CL_DEVELOPMENT"
		}
	
	filter "configurations:Preview"
		kind "ConsoleApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_PREVIEW"
		}
	
	filter "configurations:Shipping"
		kind "WindowedApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_SHIPPING"
		}
