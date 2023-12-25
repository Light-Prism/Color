#include "ColorPCH.h"
#include "LinuxMessageDialog.h"

namespace Color
{
	LinuxMessageDialog::LinuxMessageDialog(const MessageDialogProps& props)
		: m_Props(props)
	{
	}

	DialogResult LinuxMessageDialog::Create()
	{
		// Linux currently doesn't support MessageDialog.
		return DialogResult::CreationFailure;
	}

	void LinuxMessageDialog::SetCaption(const std::string& caption)
	{
		m_Props.Caption = caption;
	}

	void LinuxMessageDialog::SetContents(const std::string& contents)
	{
		m_Props.Contents = contents;
	}

	void LinuxMessageDialog::SetControls(DialogControls controls)
	{
		m_Props.Controls = controls;
	}

	void LinuxMessageDialog::SetIcon(DialogIcon icon)
	{
		m_Props.Icon = icon;
	}
}
