VULKAN_SDK = os.getenv("VULKAN_SDK")

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
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = { }
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = { }
Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

SourceDir = { }
SourceDir["Color"] = "%{ProjectDir.Color}/Source"
SourceDir["Colorful"] = "%{ProjectDir.Colorful}/Source"
SourceDir["GLFW"] = "%{ProjectDir.GLFW}/src"
SourceDir["Glad"] = "%{ProjectDir.Glad}/src"
SourceDir["Sandbox"] = "%{ProjectDir.Sandbox}/Sandbox"
