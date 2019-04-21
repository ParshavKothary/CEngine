#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#include <cstdio>
#define DEBUG_LOG(fmt, ...) CEngineDebug::_DEBUG_LOG(fmt, __VA_ARGS__)
#define DEBUG_LOG_STEP_IN CEngineDebug::_DEBUG_LOG_PLUS_LEVEL()
#define DEBUG_LOG_STEP_OUT CEngineDebug::_DEBUG_LOG_MINUS_LEVEL()
#define DEBUG_ASSERT(s) assert(s)
#else
#define DEBUG_LOG(fmt, ...) 
#define DEBUG_LOG_STEP_IN 
#define DEBUG_LOG_STEP_OUT 
#define DEBUG_ASSERT(s) 
#endif // DEBUG

class CEngineDebug
{
	friend class CECore;
#ifdef ENABLE_DEBUG
public:
	static void _DEBUG_LOG(const char* const format, ...);
	static void _DEBUG_LOG_PLUS_LEVEL();
	static void _DEBUG_LOG_MINUS_LEVEL();
private:
	static int _DEBUG_LOG_LEVEL;
#endif
};

#endif // !DEBUG_H
