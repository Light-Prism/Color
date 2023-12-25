OutputDir = { }
OutputDir["Completer"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.Completer}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir.Completer}"

ProjectDir = { }
ProjectDir["Color"] = "%{wks.location}/Engine/Color"
ProjectDir["Colorful"] = "%{wks.location}/Engine/Colorful"
ProjectDir["Sandbox"] = "%{wks.location}/Templates/Sandbox"

IncludeDir = { }
IncludeDir["Color"] = "%{ProjectDir.Color}/Source/Color"
IncludeDir["Colorful"] = "%{ProjectDir.Colorful}/Source"
IncludeDir["Sandbox"] = "%{ProjectDir.Colorful}/Sandbox"
IncludeDir["spdlog"] = "%{ProjectDir.Color}/ThirdParty/spdlog/include"

SourceDir = { }
SourceDir["Color"] = "%{ProjectDir.Color}/Source"
SourceDir["Colorful"] = "%{ProjectDir.Colorful}/Source"
SourceDir["Sandbox"] = "%{ProjectDir.Colorful}/Sandbox"
