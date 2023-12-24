#pragma once

#include <memory>
#include <string>

#define CL_CONCAT_IMPL(l, r) l##r
#define CL_CONCAT(l, r)      CL_CONCAT_IMPL(l, r)

#define CL_STRINGIFY_IMPL(x) #x
#define CL_STRINGIFY(x)      CL_STRINGIFY_IMPL(x)

namespace Color
{
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename... Args>
	constexpr Scope<T> MakeScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	enum class Compiler
	{
		Unknown,
		Clang,
		MSVC,
		GCC
	};

	struct CompilerInfo
	{
		const char* LongName;
		const char* ShortName;
		Compiler Comp;
	};

	#define IMPLEMENT_COMPILER(name, comp) inline constexpr ::Color::CompilerInfo c_CompilerInfo = { name, #comp, ::Color::Compiler::##comp }

	#ifdef __clang__
		#define CL_COMPILER_CLANG 1
		IMPLEMENT_COMPILER("Clang++", Clang);
	#elif defined _MSC_VER
		#define CL_COMPILER_CLANG 1
		IMPLEMENT_COMPILER("Microsoft Visual C++ Compiler", MSVC);
	#elif defined __GNUC__
		#define CL_COMPILER_GCC 1
		IMPLEMENT_COMPILER("GNU C++ Compiler", GCC);
	#else
		#warning This compiler isn't supported, you may run into problems! Instead, try using either MSVC, Clang or GCC.
		#define CL_COMPILER_UNKNOWN 1
		IMPLEMENT_COMPILER("Unknown C/C++ Compiler", Unknown);
	#endif

}
