// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

EVENTSSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogEventsSystem, Log, All);

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define CURRENT_FUNCTION_PRETTY_NAME __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define CURRENT_FUNCTION_PRETTY_NAME __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
	#define CURRENT_FUNCTION_PRETTY_NAME __FUNCSIG__
#elif(defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define CURRENT_FUNCTION_PRETTY_NAME __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define CURRENT_FUNCTION_PRETTY_NAME __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define CURRENT_FUNCTION_PRETTY_NAME __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define CURRENT_FUNCTION_PRETTY_NAME __func__
#else
	#define CURRENT_FUNCTION_PRETTY_NAME "(unknown)"
#endif

#define LOG_TRACE() UE_LOG(LogEventsSystem, Log, TEXT("%s"), TEXT(CURRENT_FUNCTION_PRETTY_NAME))