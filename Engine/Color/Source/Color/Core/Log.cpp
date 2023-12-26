#include "ColorPCH.h"
#include "Log.h"

#pragma warning(push, 0)
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)

namespace Color
{
	void Log::Init()
	{
		spdlog::sink_ptr sinks[] =
		{
			MakeRef<spdlog::sinks::stdout_color_sink_mt>(),
			MakeRef<spdlog::sinks::basic_file_sink_mt>("Color.log", true),
		};

		sinks[0]->set_pattern("%^[%T] %n: %v%$");
		sinks[1]->set_pattern("[%T] (%l) %n: %v");

		auto createLogger = [sinks](const std::string& name) -> Ref<Logger>
		{
			Ref<Logger> logger = MakeRef<Logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(logger);

			logger->set_level(spdlog::level::trace);
			logger->flush_on(spdlog::level::trace);

			return logger;
		};

		s_CoreLogger   = createLogger("COLOR");
		s_ClientLogger = createLogger("APP");
		s_AssertLogger = createLogger("ASSERT");
	}

	void Log::DebugPostFatalLog()
	{
		std::cout << "\x1b[33;1m  -> The application will be aborted due to that.\x1b[0m\n";
		Exit(ExitCode::LogFatal);
	}
}
