#include "Debug.h"
#ifdef ENABLE_DEBUG
#include <stdarg.h>

int CEngineDebug::_DEBUG_LOG_LEVEL = 0;

void CEngineDebug::_DEBUG_LOG(const char* const format, ...)
{
	for (int i = 0; i < _DEBUG_LOG_LEVEL; i++) printf("\t");
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
void CEngineDebug::_DEBUG_LOG_PLUS_LEVEL() { ++_DEBUG_LOG_LEVEL; }
void CEngineDebug::_DEBUG_LOG_MINUS_LEVEL() { _DEBUG_LOG_LEVEL = (_DEBUG_LOG_LEVEL == 0) ? 0 : _DEBUG_LOG_LEVEL - 1; }
#endif // ENABLE_DEBUG