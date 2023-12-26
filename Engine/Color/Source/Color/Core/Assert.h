#pragma once

#include "Core/Log.h"

#ifdef CL_PLATFORM_WINDOWS
	#define CL_DEBUGBREAK_BASE() __debugbreak()
#elif defined CL_PLATFORM_LINUX
	#include <signal.h>
	#define CL_DEBUGBREAK_BASE() raise(SIGTRAP)
#endif

#define CL_ASSERT(type, expr) {\
if (!(expr)) \
{ \
	CL_ASSERT_ERROR(type " failed! Expression was '" #expr "'!"); \
	CL_DEBUGBREAK_BASE(); \
} }

#define CL_ASSERTA(type, expr) {\
if (!(expr)) \
{ \
	CL_ASSERT_ERROR(type " failed in file '" __FILE__ "' at line " CL_STRINGIFY(__LINE__) "! Expression was '" #expr "'!"); \
	CL_DEBUGBREAK_BASE(); \
} }

#define CL_ASSERTF(type, expr, ...) {\
if (!(expr)) \
{ \
	CL_ASSERT_ERROR(type " failed! " __VA_ARGS__); \
	CL_DEBUGBREAK_BASE(); \
} }

#define CL_UNREACHABLE() \
{ \
	CL_ASSERT_ERROR("Unreachable point in file '" __FILE__ "' at line " CL_STRINGIFY(__LINE__) " was reached!"); \
	CL_DEBUGBREAK_BASE(); \
}

#define verify(expr)         CL_ASSERT("Verification", expr)
#define verifya(expr)        CL_ASSERTA("Verification", expr)
#define verifyf(expr, ...)   CL_ASSERTF("Verification", expr, __VA_ARGS__)
#define always_unreachable() CL_UNREACHABLE()

#ifndef CL_SHIPPING

#define CL_DEBUGBREAK()      CL_DEBUGBREAK_BASE()

#define check(expr)          CL_ASSERT("Check", expr)
#define checka(expr)         CL_ASSERTA("Check", expr)
#define checkf(expr, ...)    CL_ASSERTF("Check", expr, __VA_ARGS__)
#define unreachable()        CL_UNREACHABLE()

#else

#define CL_DEBUGBREAK()

#define check(expr)
#define checka(expr)
#define checkf(expr, ...)
#define unreachable()

#endif
