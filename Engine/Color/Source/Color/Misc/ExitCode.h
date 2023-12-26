#pragma once

namespace Color
{
	namespace ExitCode
	{
		using Type = int;

		enum : Type
		{
			Success    = 0, // Successful execution, no error
			Failure    = 1, // Generic/unknown failure
			NullPtr    = 2, // Null pointer error
			AllocFail  = 3, // Allocation failure
			LogFatal   = 4, // Fatal log recorded
			AssertFail = 5, // Assertion (of any sort) failure
		};
	}

	// Calls Exit on the application instance
	void Exit(ExitCode::Type exitcode);
}
