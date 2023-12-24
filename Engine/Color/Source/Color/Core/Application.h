#pragma once

#include "Core/Base.h"
#include "Misc/ExitCode.h"

namespace Color
{
	struct CommandLineArgs
	{
		static constexpr uint32_t InvalidArgIndex = 0xFFFFFFFF;

		char** List = nullptr;
		uint32_t Size = 0;

		CommandLineArgs() = default;
		CommandLineArgs(char** list, uint32_t size);

		bool Contains(const char* arg) const;
		uint32_t Find(const char* arg) const;
		uint32_t Count(const char* arg) const;

		char* At(uint32_t index) const;
		char* operator[](uint32_t index) const;
	};

	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDir;
	};

	class Application
	{
	public:
		Application() = delete;
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		Application(const CommandLineArgs& args);
		virtual ~Application();

		void Quit();
		void Exit(ExitCode::Type exitcode);

		const CommandLineArgs& GetArgs() const { return m_Args; }
		bool IsRunning() const { return m_Running; }

		static Application* Get() { return s_Instance; }
	private:
		void Run();
		void CleanUp();
	private:
		CommandLineArgs m_Args;
		bool m_Running = false;
	private:
		inline static Application* s_Instance = nullptr;
		friend int EngineMain(int, char**);
	};

	const ApplicationSpecification& GetApplicationSpecification();
	Application* CreateApplication(const CommandLineArgs&);

	#define IMPLEMENT_APPLICATION(applicationClass) \
	::Color::Application* ::Color::CreateApplication(const ::Color::CommandLineArgs& args) \
	{ \
		return new applicationClass(args); \
	}

	#define IMPLEMENT_SPECIFICATION(...) \
	const ::Color::ApplicationSpecification& ::Color::GetApplicationSpecification() \
	{ \
		static ::Color::ApplicationSpecification spec = { __VA_ARGS__ }; \
		return spec; \
	}
}
