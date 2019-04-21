#pragma once

#ifndef CE_CORE_H
#define CE_CORE_H

#include "Debug.h"

class GLWindow;

class CECore
{
public:
	static int InitEngineCore();

private:
	static GLWindow _mainWindow;

};

#endif // !CE_CORE_H