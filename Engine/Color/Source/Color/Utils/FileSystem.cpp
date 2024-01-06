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

	bool FileSystem::CreateDir(const Path& path)
	{
		return std::filesystem::create_directory(path);
	}

	bool FileSystem::CreateDirRecursive(const Path& path)
	{
		return std::filesystem::create_directories(path);
	}

	bool FileSystem::CreateNewFile(const Path& path, bool createAbsentLeadingDirectories)
	{
		if (FileSystem::Exists(path))
		{
			return false;
		}

		if (createAbsentLeadingDirectories)
		{
			Path leadingDirectories = path;
			leadingDirectories.remove_filename();

			FileSystem::CreateDirRecursive(leadingDirectories);
		}

		std::ofstream file(path, std::ios::out);
		return file.is_open();
	}

	bool FileSystem::RemoveDir(const Path& path)
	{
		return std::filesystem::remove_all(path);
	}

	bool FileSystem::RemoveFile(const Path& path)
	{
		return std::filesystem::remove(path);
	}

	std::string FileSystem::ReadFile(const Path& path, bool& outSuccess)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary);

		if (!file)
		{
			outSuccess = false;
			return "";
		}

		file.seekg(0, std::ios::end);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::string result(size, '\0');
		char* buffer = result.data();
		file.read(buffer, size);

		outSuccess = true;
		return result;
	}
}
