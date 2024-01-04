OutputDir = { }
OutputDir["Completer"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.Completer}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir.Completer}"

ProjectDir = { }
ProjectDir["Color"] = "%{wks.location}/Engine/Color"
ProjectDir["Colorful"] = "%{wks.location}/Engine/Colorful"
ProjectDir["Sandbox"] = "%{wks.location}/Templates/Sandbox"
ProjectDir["GLFW"] = "%{ProjectDir.Color}/ThirdParty/GLFW"
ProjectDir["Glad"] = "%{ProjectDir.Color}/ThirdParty/Glad"

IncludeDir = { }
IncludeDir["Color"] = "%{ProjectDir.Color}/Source/Color"
IncludeDir["Colorful"] = "%{ProjectDir.Colorful}/Source"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Sandbox"
IncludeDir["GLFW"] = "%{ProjectDir.GLFW}/include"
IncludeDir["Glad"] = "%{ProjectDir.Glad}/include"
IncludeDir["spdlog"] = "%{ProjectDir.Color}/ThirdParty/spdlog/include"
IncludeDir["glm"] = "%{ProjectDir.Color}/ThirdParty/glm"

SourceDir = { }
SourceDir["Color"] = "%{ProjectDir.Color}/Source"
SourceDir["Colorful"] = "%{ProjectDir.Colorful}/Source"
SourceDir["GLFW"] = "%{ProjectDir.GLFW}/src"
SourceDir["Glad"] = "%{ProjectDir.Glad}/src"
SourceDir["Sandbox"] = "%{ProjectDir.Sandbox}/Sandbox"
