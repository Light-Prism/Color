#pragma once

#include "Misc/MessageDialog.h"
#include "Misc/ExitCode.h"

#define SPDLOG_LEVEL_NAMES       { "trace", "debug", "info", "warn", "error", "fatal", "off" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T",     "D",     "I",    "W",     "E",    "F",     "O"   }

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Color
{
	class Logger : public spdlog::logger
	{
	public:
		template <typename It>
		Logger(std::string name, It begin, It end) : spdlog::logger(name, begin, end) { }
		virtual ~Logger() = default;

		template <typename... Args>
		void fatal(std::string_view fmt, Args&&... args)
		{
			log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
		}

		// Runtime (Dist) log
		template <typename... Args>
		void RtLog(spdlog::level::level_enum level, std::string_view fmt, Args&&... args)
		{
			const char* caption = nullptr;
			DialogIcon icon;

			switch (level)
			{
			case spdlog::level::trace:
			case spdlog::level::debug:
			case spdlog::level::info:
			{
				caption = "Runtime information";
				icon = DialogIcon::Information;
				break;
			}
			case spdlog::level::warn:
			{
				caption = "Runtime warning";
				icon = DialogIcon::Warning;
				break;
			}
			case spdlog::level::err:
			{
				caption = "Runtime error!";
				icon = DialogIcon::Error;
				break;
			}
			case spdlog::level::critical:
			{
				caption = "Fatal error!";
				icon = DialogIcon::Error;
				break;
			}
			}

			std::string msg = fmt::vformat(fmt, fmt::make_format_args(args...));
			if (level == spdlog::level::critical)
				msg += "\n\nThe application will be aborted due to that.";
				
			Scope<MessageDialog> dialog = MessageDialog::New({ caption, msg, DialogControls::Ok, icon });
			dialog->Create();

			if (level == spdlog::level::critical)
				Exit(ExitCode::LogFatal);
		}

		template <typename... Args>
		void RtTrace(std::string_view fmt, Args&&... args)
		{
			RtLog(spdlog::level::trace, fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void RtInfo(std::string_view fmt, Args&&... args)
		{
			RtLog(spdlog::level::info, fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void RtWarn(std::string_view fmt, Args&&... args)
		{
			RtLog(spdlog::level::warn, fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void RtError(std::string_view fmt, Args&&... args)
		{
			RtLog(spdlog::level::err, fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void RtFatal(std::string_view fmt, Args&&... args)
		{
			RtLog(spdlog::level::critical, fmt, std::forward<Args>(args)...);
		}
	};

	class Log
	{
	public:
		static void Init();
		static void DebugPostFatalLog();
	public:
		static Ref<Logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<Logger>& GetClientLogger() { return s_ClientLogger; }
		static Ref<Logger>& GetAssertLogger() { return s_AssertLogger; }
	private:
		inline static Ref<Logger> s_CoreLogger = nullptr;
		inline static Ref<Logger> s_ClientLogger = nullptr;
		inline static Ref<Logger> s_AssertLogger = nullptr;
	};
}

#ifndef CL_SHIPPING

#define CL_CORE_TRACE(...)     ::Color::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CL_CORE_INFO(...)      ::Color::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CL_CORE_WARN(...)      ::Color::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CL_CORE_ERROR(...)     ::Color::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CL_CORE_FATAL(...)   { ::Color::Log::GetCoreLogger()->fatal(__VA_ARGS__); ::Color::Log::DebugPostFatalLog(); }

#define CL_TRACE(...)          ::Color::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CL_INFO(...)           ::Color::Log::GetClientLogger()->info(__VA_ARGS__)
#define CL_WARN(...)           ::Color::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CL_ERROR(...)          ::Color::Log::GetClientLogger()->error(__VA_ARGS__)
#define CL_FATAL(...)        { ::Color::Log::GetClientLogger()->fatal(__VA_ARGS__); ::Color::Log::DebugPostFatalLog(); }

#define CL_ASSERT_TRACE(...)   ::Color::Log::GetAssertLogger()->trace(__VA_ARGS__)
#define CL_ASSERT_INFO(...)    ::Color::Log::GetAssertLogger()->info(__VA_ARGS__)
#define CL_ASSERT_WARN(...)    ::Color::Log::GetAssertLogger()->warn(__VA_ARGS__)
#define CL_ASSERT_ERROR(...)   ::Color::Log::GetAssertLogger()->error(__VA_ARGS__)
#define CL_ASSERT_FATAL(...) { ::Color::Log::GetAssertLogger()->fatal(__VA_ARGS__); ::Color::Log::DebugPostFatalLog(); }

#else

#define CL_CORE_TRACE(...)
#define CL_CORE_INFO(...)
#define CL_CORE_WARN(...)
#define CL_CORE_ERROR(...)     ::Color::Log::GetCoreLogger()->RtError(__VA_ARGS__)
#define CL_CORE_FATAL(...)     ::Color::Log::GetCoreLogger()->RtFatal(__VA_ARGS__)

#define CL_TRACE(...)
#define CL_INFO(...)
#define CL_WARN(...)
#define CL_ERROR(...)          ::Color::Log::GetClientLogger()->RtError(__VA_ARGS__)
#define CL_FATAL(...)          ::Color::Log::GetClientLogger()->RtFatal(__VA_ARGS__)

#define CL_ASSERT_TRACE(...)
#define CL_ASSERT_INFO(...)
#define CL_ASSERT_WARN(...)
#define CL_ASSERT_ERROR(...)   ::Color::Log::GetAssertLogger()->RtError(__VA_ARGS__)
#define CL_ASSERT_FATAL(...)   ::Color::Log::GetAssertLogger()->RtFatal(__VA_ARGS__)

#endif
