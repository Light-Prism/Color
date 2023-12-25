#include "ColorPCH.h"
#include "MessageDialog.h"

#include "Platform/Windows/WindowsMessageDialog.h"
#include "Platform/Linux/LinuxMessageDialog.h"

namespace Color
{
	Scope<MessageDialog> MessageDialog::New(const MessageDialogProps& props)
	{
		return MakeScope<ConcatWithPlatformName(MessageDialog)>(props);
	}
}
