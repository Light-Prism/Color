#include "ColorPCH.h"
#include "Application.h"

#include "Renderer/Renderer.h"
#include "Utils/FileSystem.h"

namespace Color
{
	Application::Application(const CommandLineArgs& args)
		: m_Args(args)
	{
		checkf(!s_Instance, "An application instance already exists!");
		s_Instance = this;

		Log::Init();
		CL_CORE_INFO("Initialized logging.");

		CL_CORE_INFO("Engine Build Info:");
		CL_CORE_INFO("  Compiler         -> {0} ({1})", c_CompilerInfo.LongName, c_CompilerInfo.ShortName);
		CL_CORE_INFO("  Compilation Date -> {0}", __DATE__);
		CL_CORE_INFO("  Compilation Time -> {0}", __TIME__);

		const ApplicationSpecification& spec = GetApplicationSpecification();
		{
			FileSystem::Path curWorkingDir = FileSystem::Abs(FileSystem::GetWorkingDir());
			FileSystem::Path reqWorkingDir = FileSystem::Abs(spec.WorkingDir);

			if (FileSystem::IsDir(reqWorkingDir) && curWorkingDir != reqWorkingDir)
			{
				CL_CORE_WARN("Application has requested a different working directory than the current one.");
				CL_CORE_WARN("  Current Working Directory   -> {0}", curWorkingDir);
				CL_CORE_WARN("  Requested Working Directory -> {0}", reqWorkingDir);

				FileSystem::SetWorkingDir(reqWorkingDir);
				CL_CORE_TRACE("Changed the working directory to -> {0}", FileSystem::Abs(FileSystem::GetWorkingDir()));
			}
		}

		CL_CORE_INFO("Selected Graphics API -> {0}", RendererAPI::APIToString(RendererAPI::GetAPI()));

		m_Window = Window::New(spec.WndProps);
		if (!m_Window->Init())
			CL_CORE_FATAL("Window creation failure!");

		Renderer::Init();
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
			CL_CORE_WARN("Cannot re-run an already running application instance!");
			return;
		}

		m_Running = true;

		while (m_Running)
		{
			m_Window->Update();
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
			CL_CORE_WARN("Cannot quit from a non-running application instance!");
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
		checkf(index < Size, "Index out of bounds!");
		return List[index];
	}

	char* CommandLineArgs::operator[](uint32_t index) const
	{
		verifyf(index < Size, "Index out of bounds!");
		return List[index];
	}
}
