#include "ColorPCH.h"
#include "Application.h"

namespace Color
{
	Application::Application(const CommandLineArgs& args)
		: m_Args(args)
	{
		// TODO: Check instance validity
		s_Instance = this;

		const ApplicationSpecification& spec = GetApplicationSpecification();
		{
		}
	}

	Application::~Application()
	{
		if (this == s_Instance)
			s_Instance = nullptr;
	}

	void Application::Run()
	{
		if (m_Running)
		{
			// TODO: Warn
			return;
		}

		m_Running = true;

		while (m_Running)
		{

		}

		CleanUp();
	}

	void Application::CleanUp()
	{
		// ...
	}

	void Application::Quit()
	{
		if (!m_Running)
		{
			// TODO: Warn
			return;
		}

		m_Running = false;
	}

	void Application::Exit(ExitCode::Type exitcode)
	{
		std::exit(exitcode);
	}

	CommandLineArgs::CommandLineArgs(char** list, uint32_t size)
		: List(list), Size(size)
	{
	}

	bool CommandLineArgs::Contains(const char* arg) const
	{
		for (uint32_t i = 0; i < Size; i++)
		{
			if (strcmp(List[i], arg) == 0)
				return true;
		}

		return false;
	}

	uint32_t CommandLineArgs::Find(const char* arg) const
	{
		for (uint32_t i = 0; i < Size; i++)
		{
			if (strcmp(List[i], arg) == 0)
				return i;
		}

		return InvalidArgIndex;
	}

	uint32_t CommandLineArgs::Count(const char* arg) const
	{
		uint32_t count{};

		for (uint32_t i = 0; i < Size; i++)
		{
			if (strcmp(List[i], arg) == 0)
				count++;
		}

		return count;
	}

	char* CommandLineArgs::At(uint32_t index) const
	{
		// TODO: Bounds checking
		return List[index];
	}

	char* CommandLineArgs::operator[](uint32_t index) const
	{
		// TODO: Bounds checking
		return List[index];
	}
}
