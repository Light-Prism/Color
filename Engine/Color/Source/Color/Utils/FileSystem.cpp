#include "ColorPCH.h"
#include "FileSystem.h"

namespace Color
{
	FileSystem::Path FileSystem::GetWorkingDir()
	{
		return std::filesystem::current_path();
	}

	void FileSystem::SetWorkingDir(const Path& dir)
	{
		std::filesystem::current_path(dir);
	}

	FileSystem::Path FileSystem::Abs(const Path& path)
	{
		return std::filesystem::absolute(path);
	}

	FileSystem::Path FileSystem::Rel(const Path& path)
	{
		return std::filesystem::relative(path);
	}

	bool FileSystem::IsFile(const Path& path)
	{
		return std::filesystem::is_regular_file(path);
	}

	bool FileSystem::IsDir(const Path& path)
	{
		return std::filesystem::is_directory(path);
	}

	bool FileSystem::Exists(const Path& path)
	{
		return std::filesystem::exists(path);
	}

	bool FileSystem::FileExists(const Path& path)
	{
		return Exists(path) && IsFile(path);
	}

	bool FileSystem::DirExists(const Path& path)
	{
		return Exists(path) && IsDir(path);
	}
}
