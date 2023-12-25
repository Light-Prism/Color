#pragma once

#include "Core/Base.h"

namespace Color
{
	enum class DialogControls : long
	{
		AbortRetryIgnore  = 0x00000002L,
		CancelTryContinue = 0x00000006L,
		Help              = 0x00004000L,
		Ok                = 0x00000000L,
		OkCancel          = 0x00000001L,
		RetryCancel       = 0x00000005L,
		YesNo             = 0x00000004L,
		YesNoCancel       = 0x00000003L
	};

	enum class DialogIcon : long
	{
		Question    = 0x00000020L,
		Information = 0x00000040L,
		Warning     = 0x00000030L,
		Error       = 0x00000010L
	};

	enum class DialogResult
	{
		CreationFailure = -1,

		Ok       = 1,
		Cancel   = 2,
		Abort    = 3,
		Retry    = 4,
		Ignore   = 5,
		Yes      = 6,
		No       = 7,
		TryAgain = 10,
		Continue = 11
	};

	struct MessageDialogProps
	{
		std::string Caption;
		std::string Contents;
		DialogControls Controls;
		DialogIcon Icon;

		MessageDialogProps(const std::string& caption = "Untitled Message Dialog",
						   const std::string& contents = "Sample Message Dialog",
						   DialogControls controls = DialogControls::Ok,
						   DialogIcon icon = DialogIcon::Information)
			: Caption(caption), Contents(contents), Controls(controls), Icon(icon) { }
	};

	class MessageDialog
	{
	public:
		virtual ~MessageDialog() = default;

		virtual DialogResult Create() = 0;

		virtual void SetCaption(const std::string& caption) = 0;
		virtual void SetContents(const std::string& contents) = 0;
		virtual void SetControls(DialogControls controls) = 0;
		virtual void SetIcon(DialogIcon icon) = 0;
		
		virtual const std::string& GetCaption() const = 0;
		virtual const std::string& GetContents() const = 0;
		virtual DialogControls GetControls() const = 0;
		virtual DialogIcon GetIcon() const = 0;

		static Scope<MessageDialog> New(const MessageDialogProps& props = { });
	};
}
