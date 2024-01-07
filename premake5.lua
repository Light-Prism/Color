workspace "Color"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Development",
		"Preview",
		"Shipping"
	}

include "Globals.lua"

group "Engine/ThirdParty"
	include "Engine/Color/ThirdParty/GLFW"
	include "Engine/Color/ThirdParty/Glad"
	include "Engine/Color/ThirdParty/stb"
group ""

group "Engine"
	include "Engine/Color"
	include "Engine/Colorful"
group ""

group "Templates"
	include "Templates/Sandbox"
group ""
