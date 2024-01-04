#include "ColorPCH.h"
#include "RenderCommand.h"

namespace Color
{
	Scope<RendererAPI> RenderCommand::s_API = RendererAPI::New();
}
