#pragma once

#include "Core/Base.h"

#include <filesystem>

namespace Color
{
	class FileSystem
	{
	public:
		using Path = std::filesystem::path;
	public:
		static Path GetWorkingDir();
		static void SetWorkingDir(const Path& dir);

		static Path Abs(const Path& path);
		static Path Rel(const Path& path);

		static bool IsFile(const Path& path);
		static bool IsDir(const Path& path);

		static bool Exists(const Path& path);
		static bool FileExists(const Path& path);
		static bool DirExists(const Path& path);

		static bool CreateDir(const Path& path);
		static bool CreateDirRecursive(const Path& path);
		static bool CreateNewFile(const Path& path, bool createAbsentLeadingDirectories = true);

		static bool RemoveDir(const Path& path);
		static bool RemoveFile(const Path& path);

		static std::string ReadFile(const Path& path, bool& outSuccess);
	};
}
