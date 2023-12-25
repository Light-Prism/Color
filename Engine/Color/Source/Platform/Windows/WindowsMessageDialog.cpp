#include "ColorPCH.h"
#include "WindowsMessageDialog.h"

namespace Color
{
	WindowsMessageDialog::WindowsMessageDialog(const MessageDialogProps& props)
		: m_Props(props)
	{
	}

	DialogResult WindowsMessageDialog::Create()
	{
		return (DialogResult) MessageBoxA(
			NULL,
			m_Props.Contents.c_str(),
			m_Props.Caption.c_str(),
			(UINT)((long) m_Props.Controls | (long) m_Props.Icon)
		);
	}

	void WindowsMessageDialog::SetCaption(const std::string& caption)
	{
		m_Props.Caption = caption;
	}

	void WindowsMessageDialog::SetContents(const std::string& contents)
	{
		m_Props.Contents = contents;
	}

	void WindowsMessageDialog::SetControls(DialogControls controls)
	{
		m_Props.Controls = controls;
	}

	void WindowsMessageDialog::SetIcon(DialogIcon icon)
	{
		m_Props.Icon = icon;
	}
}
