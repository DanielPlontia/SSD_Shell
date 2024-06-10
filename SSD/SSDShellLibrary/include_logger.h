#pragma once
#include "../logger/Logger.h"

#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/logger.lib")
#else
#pragma comment (lib, "../x64/Release/logger.lib")
#endif // _DEBUG
