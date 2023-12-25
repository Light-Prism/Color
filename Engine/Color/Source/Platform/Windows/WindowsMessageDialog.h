#pragma once

#include "Misc/MessageDialog.h"

namespace Color
{
	class WindowsMessageDialog : public MessageDialog
	{
	public:
		WindowsMessageDialog(const MessageDialogProps& props);
		virtual ~WindowsMessageDialog() = default;

		virtual DialogResult Create() override;

		virtual void SetCaption(const std::string& caption) override;
		virtual void SetContents(const std::string& contents) override;
		virtual void SetControls(DialogControls controls) override;
		virtual void SetIcon(DialogIcon icon) override;

		virtual const std::string& GetCaption() const override { return m_Props.Caption; }
		virtual const std::string& GetContents() const override { return m_Props.Contents; }
		virtual DialogControls GetControls() const override { return m_Props.Controls; }
		virtual DialogIcon GetIcon() const override { return m_Props.Icon; }
	private:
		MessageDialogProps m_Props;
	};
}
